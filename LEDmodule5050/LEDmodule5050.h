#ifndef FULLCOLORLEDMODULE_H
#define FULLCOLORLEDMODULE_H
#include "arduino.h"

typedef  uint32_t color;

class FullColorLedModule {
public:
	// r pin number for red Led
	// g pin number for Green Led
	// b pin number for blue Led
	// n number of connected Leds
	// pins array with size of n with pinnumbers, leds are adressed as indexes in this array  
	FullColorLedModule(uint8_t r,uint8_t g,uint8_t b,uint8_t n,uint8_t pins[]);		// Defines pins to use
	~FullColorLedModule();
	void Setup();
	// On functions
	
	
	void On();
	// light Led index with color c
	void On(color c,uint8_t index);
	// light leds in array all with color c
	void On(color c,uint8_t n,uint8_t index[]);
	// light multiple leds with each another color in 2 arrays
	void On(uint8_t n,color c[],uint8_t index[]);

	// switches led index on with last set color 
	void On(uint8_t index);
	// switches led index-array on with last set color
	void On(uint8_t n,uint8_t index[]);

	// Switch all LEDs off
	void Off();
	// Switch LED index off
	void Off(uint8_t index);
	// Switches all LEDs in index array off
	void Off(uint8_t n, uint8_t index[]);
	// in all Off methods the last set color is maintained.
	
//	void Poll();	// for now the way to light them 
	void Dump();	// test method
	
	// color oonstants
	static const color	_Off;
	static const color	_White;
	static const color	_HalfWhite;
	static const color  _Green;
	static const color	_Red;
	static const color	_Blue;
	static const color	_Margenta;
	static const color	_Purple;
	static const color	_Black;
	
protected:
	uint8_t CorrectMax(uint8_t size);	// cheack array Size and if tho large return max size
public:
	static uint8_t _RedPin;		//	pin that controls Red color preferable PWM pin
	static uint8_t _GreenPin;		//	pin that controls Green color preferable PWM pin
	static uint8_t _BluePin;		//	pin that controls Bleu color preferable PWM pin

	static uint8_t*	_LEDPins;	// array containing the pins
	static uint8_t	_Leds;		// numbers of LED-pins
	static color*	_Colors;
	
	static const uint8_t	_MaxLEDs ;	// max pins determined by hardware
    static uint8_t _CurrLed;
};

#endif  //FULLCOLORLEDMODULE_H