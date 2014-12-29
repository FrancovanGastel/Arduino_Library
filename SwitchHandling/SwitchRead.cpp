#include "SwitchRead.h"
#include "Arduino.h"

// TODO make it with interrupt handing 
// i.s.o. polling preferably confirurable 

volatile bool	SwitchRead::_tlPin2 = false;
volatile bool	SwitchRead::_ttPin2	= false;
volatile bool  	SwitchRead::_LastState2 = false;

volatile bool	SwitchRead::_tlPin3 = false;
volatile bool	SwitchRead::_ttPin3 = false;
volatile bool  	SwitchRead::_LastState3= false;

int				SwitchRead::_Size;

volatile bool  	SwitchRead::_tlPins[_maxSize];     		// trailing edge triggered
volatile bool  	SwitchRead::_ttPins[_maxSize];  	    // leading edge triggered
volatile bool  	SwitchRead::_LastStatePins[_maxSize];   //
uint8_t  SwitchRead::_pins[_maxSize];          	// pins number

SwitchRead::SwitchRead()
{
	_Size = 0;
	_int0= false;
	_int1= false;
	Setup();
}

SwitchRead::SwitchRead(uint8_t pin1)
{
	_Size = 1;
	_pins[0] = pin1;
	CheckForInterrupts();
	Setup();
}

SwitchRead::SwitchRead(uint8_t pin1, uint8_t pin2)
{
	_Size = 2;
	_pins[0] = pin1;
	_pins[1] = pin2;
	CheckForInterrupts();
	Setup();
}

SwitchRead::SwitchRead(uint8_t pin1, uint8_t pin2, uint8_t pin3)
{
	_Size = 3;
	_pins[0] = pin1;
	_pins[1] = pin2;
	_pins[2] = pin3;
	CheckForInterrupts();
	Setup();
}

SwitchRead::SwitchRead(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4)
{
	_Size = 4;
	_pins[0] = pin1;
	_pins[1] = pin2;
	_pins[2] = pin3;
	_pins[3] = pin4;
	CheckForInterrupts();
	Setup();
}

SwitchRead::SwitchRead(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin5)
{
	_Size = 5;
	_pins[0] = pin1;
	_pins[1] = pin2;
	_pins[2] = pin3;
	_pins[3] = pin4;
	_pins[4] = pin5;
	CheckForInterrupts();
	Setup();
}

SwitchRead::SwitchRead(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin5, uint8_t pin6)
{
	_Size = 6;
	_pins[0] = pin1;
	_pins[1] = pin2;
	_pins[2] = pin3;
	_pins[3] = pin4;
	_pins[4] = pin5;
	_pins[5] = pin6;
	CheckForInterrupts();
	Setup();
}

SwitchRead::~SwitchRead()
{
	if(_int0) detachInterrupt(0);
	if(_int1) detachInterrupt(1);
}

void SwitchRead::Poll()
{
	bool _curr;
	for(int i=0;i<_Size;i++)
	{
		_curr=digitalRead(_pins[i]);
		Test(i,_curr);
	}	
}

void SwitchRead::Reset()
{
	for(int i=0;i<_Size;i++)
	{
		_tlPins[i] = false;
		_ttPins[i] = false;
	}
	_tlPin2 = false;
	_ttPin2 = false;
	_tlPin3 = false;
	_ttPin3 = false;
}

int  SwitchRead::GetSize()
{
	return _maxSize;
}

bool SwitchRead::tlSwitch(uint8_t pin)
{
	if( (pin==2)||(pin==3))
	{	// test leading edge for interruots
		if(pin==2)	return _tlPin2;
		else		return _tlPin3;
	}
	else
	{
		// test leading edge
		uint8_t index=0; 
		while(index<_Size && pin != _pins[index]) index++;
		return _tlPins[index];
	}
}

bool SwitchRead::tlcSwitch(uint8_t pin)
{
	if( (pin==2)||(pin==3))
	{	// test leading edge for interruots
		bool bRetVar;
		if(pin==2)
		{
			bRetVar = _tlPin2;
			_tlPin2 = false;
		}
		else
		{
			bRetVar = _tlPin3;
			_tlPin3 = false;
		}
		return bRetVar;
	}
	else
	{
		// test and clear leading edge
		int index=0; 
		while(index<_Size && pin != _pins[index]) index++;
	
		bool retvar = _tlPins[index];
		_tlPins[index] = false;
		
		return retvar;
	}
}

void SwitchRead::lcSwitch(uint8_t pin)
{
	if( (pin==2)||(pin==3))
	{
		if(pin==2)	_tlPin2 = false;
		else		_tlPin3 = false;
	} else
	{
		// clear leading edge
		int index=0; 
		while(index<_Size && pin != _pins[index]) index++;
		_tlPins[index] = false;
	}
}

void SwitchRead::wlSwitch(uint8_t pin)
{
	// blokcing wait for leading edge
	do
	{
		Poll();
	}
	while(tlSwitch(pin));
}

bool SwitchRead::wlSwitch(uint8_t pin, int timeout)
{
	// blokcing wait for leading edge
	int timeCounter=0;
	do
	{
		Poll();
	}
	while(tlSwitch(pin) && timeCounter++<timeout);
	return(timeCounter<timeout);		// retrun false if timeout
}

bool SwitchRead::ttSwitch(uint8_t pin)
{ 
	if( (pin==2)||(pin==3))
	{	// test leading edge for interruots
		if(pin==2)	return _tlPin2;
		else		return _tlPin3;
	}
	else
	{
		// test trailing edge
		int index=0; 
		while(index<_Size && pin != _pins[index]) index++;
			
		return _ttPins[index];
	}
}

bool SwitchRead::ttcSwitch(uint8_t pin)
{
	if( (pin==2)||(pin==3))
	{	// test leading edge for interruots
		bool bRetVar;
		if(pin==2)
		{
			bRetVar = _tlPin2;
			_tlPin2 = false;
		}
		else
		{
			bRetVar = _tlPin3;
			_tlPin3 = false;
		}
		return bRetVar;
	}
	else
	{
		// test and clear trailing edge
		int index=0; 
		while(index<_Size && pin != _pins[index]) index++;
	
		bool retvar = _ttPins[index];
		_ttPins[index] = false;
		return retvar;
	}
}

void SwitchRead::tcSwitch(uint8_t pin)
{
	if( (pin==2)||(pin==3))
	{
		if(pin==2)	_tlPin2 = false;
		else		_tlPin3 = false;
	} 
	else
	{
		// clear trailing edge
		int index=0; 
		while(index<_Size && pin != _pins[index]) index++;
		_ttPins[index] = false;
	}
}

void SwitchRead::wtSwitch(uint8_t pin)
{
	// blokcing wait for trailing edge
	do
	{
		Poll();
	}
	while(tlSwitch(pin));
}

bool SwitchRead::wtSwitch(uint8_t pin, int timeout)
{
	// blokcing wait for leading edge
	int timeCounter=0;
	do
	{
		Poll();
	}
	while(tlSwitch(pin) && timeCounter++<timeout);
	
	return(timeCounter<timeout);		// retrun false if timeout
}

bool SwitchRead::tSwitch(uint8_t pin)
{
	       // read current state
	return digitalRead(pin);
}

void SwitchRead::Test(int i,bool _curr)
{
	if(_curr==false)
	{
		if(_LastStatePins[i]==true) _ttPins[i]=true;
	}	
	else
	{
		if(_LastStatePins[i]==false) _tlPins[i]=true;
	}
	_LastStatePins[i]=_curr;
}

void SwitchRead::TheInterruptRoutine0()
{
	bool _curr=digitalRead(2);
	if(_curr==false)
	{
		if(_LastState2==true) _ttPin2=true;
	}	
	else
	{
		if(_LastState2==false) _tlPin2=true;
	}
	_LastState2=_curr;
}

void SwitchRead::TheInterruptRoutine1()
{
	bool _curr=digitalRead(3);
	if(_curr==false)
	{
		if(_LastState3==true) _ttPin3=true;
	}	
	else
	{
		if(_LastState3==false) _tlPin3=true;
	}
	_LastState3=_curr;
}

void SwitchRead::CheckForInterrupts()
{
	_int0 = false;
	_int1 = false;
	for(int i=0;i<_Size;i++)
	{
		if(_pins[i]==2)
		{
			_int0 = true;
			attachInterrupt(0,&SwitchRead::TheInterruptRoutine0,CHANGE);
		} else if(_pins[i]==3)
		{
			_int1 = true;
			attachInterrupt(1,&SwitchRead::TheInterruptRoutine1,CHANGE);
		}
	}	
}


void SwitchRead::Setup()
{
	// setup interrupt 
	noInterrupts();
	
	TCCR1A=0;
	TCCR1B=0;
	TCNT1 =0;
	
	OCR1A = 125;
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS12);
	TIMSK1 |= (1 << OCIE1A);
	interrupts();
}

ISR(TIMER1_COMPA_vect)
{
	bool _curr;
	for(int i=0;i<SwitchRead::_Size;i++)
	{
		_curr=digitalRead(SwitchRead::_pins[i]);
		if(_curr==false)
			{
				if(SwitchRead::_LastStatePins[i]==true) SwitchRead::_ttPins[i]=true;
			}	
			else
			{
				if(SwitchRead::_LastStatePins[i]==false) SwitchRead::_tlPins[i]=true;
			}
		SwitchRead::_LastStatePins[i]=_curr;
	}	
}
