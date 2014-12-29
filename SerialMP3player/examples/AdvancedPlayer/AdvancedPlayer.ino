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
  MP3.Reset();
  MP3.SetVolume(15);
}

bool  bRepeatOn = false;


void loop()
{
  int v= analogRead(A0);
  int vol = map(v,0,1023,0,30);
  MP3.SetVolume(vol);
  
   Switches.Poll();
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
     int  songs[3] = { 2,1,5 };
     MP3.PlayGroup(3, songs);
   }
   

   if(Switches.tlcSwitch(PinTest2))
   {
     MP3.PlayAtVolume(2,10);
   }

   if(Switches.tlcSwitch(PinTest3))
   {
     MP3.Play(1,1);
   }
   delay(25);
}

bool Toggle(bool b)
{
  return !b;
}
