#include "LEDmodule5050.h"
#include "Arduino.h"

	const uint8_t	FullColorLedModule::_MaxLEDs = 8;	// max pins determined by hardware
	
	uint8_t*	FullColorLedModule::_LEDPins;	// array containing the pins
	color*		FullColorLedModule::_Colors;
	uint8_t 	FullColorLedModule::_RedPin;
	uint8_t 	FullColorLedModule::_GreenPin;
	uint8_t 	FullColorLedModule::_BluePin;
	uint8_t		FullColorLedModule::_Leds;
	
	const color	FullColorLedModule::_Off = 0x1FFFFFF;
	const color	FullColorLedModule::_White= 0x000000;
	const color	FullColorLedModule::_HalfWhite= 0xcfcfcf;
	const color	FullColorLedModule::_Red = 0xffff00;
	const color	FullColorLedModule::_Green = 0x00ffff;
	const color	FullColorLedModule::_Blue = 0xff00ff;
	const color	FullColorLedModule::_Margenta = 0x000000ff;
	const color	FullColorLedModule::_Purple  = 0x00FF0000;
	const color	FullColorLedModule::_Black= 0x00FFFFFF;
	

uint8_t FullColorLedModule::_CurrLed;

FullColorLedModule::FullColorLedModule(uint8_t r,uint8_t g,uint8_t b,uint8_t n, uint8_t a[])
{
	_CurrLed=0;
	_Leds = (_Leds>_MaxLEDs) ? _MaxLEDs : n;  
	
	_LEDPins = new uint8_t[_Leds];
	_Colors  = new color[_Leds];
	
	_RedPin   = r;
	_GreenPin = g;
	_BluePin  = b;
	
	pinMode(_RedPin,OUTPUT);
	pinMode(_GreenPin,OUTPUT);
	pinMode(_BluePin,OUTPUT);
	
	for(uint8_t i = 0; i< _Leds; i++)
	{
		_LEDPins[i] = a[i];
		pinMode(_LEDPins[i],OUTPUT);
		digitalWrite(_LEDPins[i], HIGH);		 // all switched off @ initialisation
		_Colors[i] = _Off | 0x00ff00;
	}
	Setup();
}

void FullColorLedModule::Setup()
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
	digitalWrite(FullColorLedModule::_LEDPins[FullColorLedModule::_CurrLed], HIGH);
	FullColorLedModule::_CurrLed++;
	if(FullColorLedModule::_CurrLed>=8) FullColorLedModule::_CurrLed=0;
	bool _OffSet = bitRead(FullColorLedModule::_Colors[FullColorLedModule::_CurrLed],24);
	
	if(!_OffSet)
	{
		uint32_t val;
		val = FullColorLedModule::_Colors[FullColorLedModule::_CurrLed] & 0xFF;
		analogWrite(FullColorLedModule::_RedPin,(uint8_t) val);
		
		val = (FullColorLedModule::_Colors[FullColorLedModule::_CurrLed]>>8) & 0xFF;
		analogWrite(FullColorLedModule::_GreenPin,(uint8_t) val);
			
		val = (FullColorLedModule::_Colors[FullColorLedModule::_CurrLed]>>16) & 0xFF;
		analogWrite(FullColorLedModule::_BluePin,(uint8_t) val);
		
		digitalWrite(FullColorLedModule::_LEDPins[FullColorLedModule::_CurrLed], LOW);
	}
}


FullColorLedModule::~FullColorLedModule()
{
	delete [] _LEDPins;
	delete [] _Colors;
}
	
void FullColorLedModule::On()
{
//	Serial.print("On()");
	for(uint8_t i = 0; i<_Leds; i++)
	{
		_Colors[i] &= _White; // clear off bit
	}
//	Poll();

}

void FullColorLedModule::On(color c,uint8_t index)
{
//	Serial.print("On(color c,uint8_t index)");
	_Colors[index]=c;
//	Poll();
}

void FullColorLedModule::On(uint8_t index)
{
//	Serial.print("On(uint8_t index ");
	
	_Colors[index] &= 0xffffff;
	
	Serial.println(_Colors[index]);
//	Poll();
}

void FullColorLedModule::On(color c,uint8_t n,uint8_t index[])
{
//	Serial.print("On(color c,uint8_t index[])");
	uint8_t s = CorrectMax(n);
	for(uint8_t i = 0; i<s; i++)
	{
		_Colors[index[i]]=c;
	}
//	Poll();
}

void FullColorLedModule::On(uint8_t n, uint8_t index[])
{
//	Serial.print("On(uint8_t index[])");
	
	uint8_t s = CorrectMax(n);
	for(uint8_t i = 0; i<s; i++)
	{
		_Colors[index[i]] &= 0xffffff;
	}
//	Poll();
}


void FullColorLedModule::On(uint8_t n,color c[],uint8_t index[])
{
//	Serial.print("color c[],uint8_t index[]");
	uint8_t si=CorrectMax(n);
	for(uint8_t i = 0; i<si; i++)
	{
		_Colors[index[i]]=c[i];
	}	
//	Poll();
}

void FullColorLedModule::Off()
{
//	Serial.print("Off()");
	for(uint8_t i = 0; i<_Leds; i++)
	{
		_Colors[i]|=_Off;
	}
//	Poll();
}

void FullColorLedModule::Off(uint8_t index)
{
//	Serial.print("Off(uint8_t index)");
	_Colors[index]|=_Off;
//	Poll();
}

void FullColorLedModule::Off(uint8_t n, uint8_t index[])
{
//	Serial.print("Off(uint8_t index[])");
	uint8_t si=CorrectMax(n);
	
	for(uint8_t i = 0; i<si; i++)
	{
		_Colors[index[i]]|=_Off;
	}
//	Poll();
}

/*
void FullColorLedModule::Poll()
{
	// pollen op andere manier
	// constant kleuren en pin aansturen
	
	digitalWrite(_LEDPins[_CurrLed], HIGH);
	_CurrLed++;
	if(_CurrLed>=8) _CurrLed=0;
	bool _OffSet = bitRead(_Colors[_CurrLed],24);
	
	if(!_OffSet)
	{
		uint32_t val;
		val = _Colors[_CurrLed] & 0xFF;
		analogWrite(_RedPin,(uint8_t) val);
		
		val = (_Colors[_CurrLed]>>8) & 0xFF;
		analogWrite(_GreenPin,(uint8_t) val);
			
		val = (_Colors[_CurrLed]>>16) & 0xFF;
		analogWrite(_BluePin,(uint8_t) val);
		
		digitalWrite(_LEDPins[_CurrLed], LOW);
	}
}*/

uint8_t FullColorLedModule::CorrectMax(uint8_t size)
{
	return (size>_Leds) ? _Leds:size;
}

void FullColorLedModule::Dump()
{
	Serial.println();
	
	Serial.print("Leds ");
	Serial.print(_Leds);
	Serial.print(" green: ");
	Serial.print(_GreenPin);
	Serial.print(" Red: ");
	Serial.print(_RedPin);
	Serial.print(" Blue: ");
	Serial.println(_BluePin);
	
	for(int i =0; i<8;i++)
	{
		Serial.print(i);
		Serial.print(": pin[");
		Serial.print(_LEDPins[i]);
		Serial.print("] = color ");
		Serial.println(_Colors[i]);
	}
}
