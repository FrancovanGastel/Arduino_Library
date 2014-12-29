#ifndef SwitchRead_h
#define SwitchRead_h

#include "pins_arduino.h"
//************************************************************************************************
// SwitchRead library
// ***********************************************************************************************
//
// Programmed by Franco van Gastel
//
//		franco@familievangastel.com
//	date: 	23-11-2014				Versiom 1.0b
//------------------------------------------------------------------------------------------------
// Desciption:
//    Libraby van be used to test for leading Edge, trailing edge, and current state.
//	  in order for responsiveness make sure the poll routine is called every 100 ms.
//    
//	  During initialize define pins to use
//    You should declare pinMode youself in setup !!!!
//
//------------------------------------------------------------------------------------------------
//
//	  possible impromvements:
// 		*	TODO make it with interrupt handing 
// 			i.s.o. polling preferably confirurable 
// 		*	Set pinmode inm constructors
//	
//	
// ***********************************************************************************************

#define _maxSize 6

class SwitchRead
{
public:
  SwitchRead(uint8_t pin1);
  SwitchRead(uint8_t pin1, uint8_t pin2);
  SwitchRead(uint8_t pin1, uint8_t pin2, uint8_t pin3);
  SwitchRead(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);
  SwitchRead(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin5);
  SwitchRead(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin5, uint8_t pin6);
  ~SwitchRead();

  static void Poll();
  void Reset();
  int  GetSize();
   
static  bool tlSwitch(uint8_t pin);      // test leading edge
static  bool tlcSwitch(uint8_t pin);    // test and clear leading edge
static  void lcSwitch(uint8_t pin);      // clear leading edge
static  void wlSwitch(uint8_t pin);      // blokcing wait for leading edge
static  bool wlSwitch(uint8_t pin,int timeout);      // blokcing wait for trailing edge
  
static    bool ttSwitch(uint8_t pin);      // test trailing edge
static    bool ttcSwitch(uint8_t pin);    // test and clear trailing edge
static    void tcSwitch(uint8_t pin);      // clear trailing edge
static  void wtSwitch(uint8_t pin);      // blokcing wait for trailing edge
static    bool wtSwitch(uint8_t pin,int timeout);      // blokcing wait for trailing edge

static  bool tSwitch(uint8_t pin);       // read current state
  
  protected:
  // index based acces for derived classes 
  // functions need to test index them selves agains overflow using next method
  
static  bool		isIndexValid(const uint8_t i)  { return (i<_maxSize);};
  void 		Setup();
    
  uint8_t	index2pin(uint8_t i ) { return _pins[i];}; 	
  bool	 	getTStateIndex(uint8_t i) { return _tlPins[i];};
  bool 		getLStateIndex(uint8_t i) { return _ttPins[i];};
  void	 	setTStateIndex(uint8_t i, bool b) { _tlPins[i]=b;};
  void 		setLStateIndex(uint8_t i, bool b) { _ttPins[i]=b;};
  
  static 	void		Test(int i,bool _curr);
 
  private:
  SwitchRead();
  
  void 		CheckForInterrupts();
//  friend void		TheInterruptRoutine0();
//  friend void		TheInterruptRoutine1();

  static void		TheInterruptRoutine0();
  static void		TheInterruptRoutine1();

  private:
  
  
  public:
  static uint8_t  	_pins[_maxSize];          	// pins number
  static int		_Size;
  volatile static  bool  	_tlPins[_maxSize];     		// trailing edge triggered
  volatile static  bool  	_ttPins[_maxSize];  	    // leading edge triggered
  volatile static  bool  	_LastStatePins[_maxSize];   //
  
  private:
  volatile static bool	_tlPin2;
  volatile static bool	_ttPin2;
  volatile static bool  _LastState2;
  
  volatile static bool	_tlPin3;
  volatile static bool	_ttPin3;
  volatile static bool  _LastState3;

  
  bool _int0;
  bool _int1;
};


#endif
