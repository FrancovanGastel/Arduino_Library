#include "SerialMP3Player.h"
#include <SwitchRead.h>
#include <SoftwareSerial.h>

int PinStop   = 4;      // start button
int PinStart  = 3;      // Stop button

int PinTest1  = 8;      // Test Button 1
int PinTest2  = 9;      // Test button 2
int PinTest3  =10;      // Test button 3

int PinTestLed   =13;   // Control light Which is on when MP3 is playing

int  PinRx    = 5;      // Rx Pin of MP3
int  PinTx    = 6;      // Tx Pin of MP3


SwitchRead        Switches(PinStart,PinStop,PinTest1,PinTest2,PinTest3);
SerialMP3Player   MP3(PinRx,PinTx);

void setup()
{
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(PinTestLed,OUTPUT);

  MP3.Setup();
}

bool  bRepeatOn = false;


void loop()
{
   int val = analogRead(A0);
   int volume = map(val,0,1023,0,30);
   
   MP3.SetVolume(volume);
   
   if(Switches.tlcSwitch(PinStart))
   {
       MP3.Play();
       digitalWrite(13,HIGH);
       
   }
   if(Switches.tlcSwitch(PinStop))
   {
     MP3.Stop();
     digitalWrite(13,LOW);   
   }
   
   if(Switches.tlcSwitch(PinTest1))
   {
     Toggle(bRepeatOn);
     if(bRepeatOn)
       MP3.PlayRepeat();
     else
       MP3.StopRepeat();     
   }
   

   if(Switches.tlcSwitch(PinTest2))
   {
      MP3.PlayShuffle();   
   }

   if(Switches.tlcSwitch(PinTest3))
   {
     MP3.Play(5);
   }
}

bool Toggle(bool b)
{
  return !b;
}
