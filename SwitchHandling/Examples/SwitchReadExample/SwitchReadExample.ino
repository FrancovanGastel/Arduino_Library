#include <SwitchRead.h>


SwitchRead sr(12,7,6);

void setup()
{
  pinMode(12,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  
  sr.Reset();
  Serial.begin(9600);
  
}

void loop()
{
 sr.Poll();
 if(sr.tlcSwitch(13))
 {
   Serial.println("sr.tlcswitch(13)");
 }
 if(sr.tlcSwitch(6))
 {
   Serial.println("sr.tlcswitch(13)");
 }
 if(sr.tlcSwitch(7))
 {
   Serial.println("sr.tlcswitch(13)");
 }

 
 if(sr.ttcSwitch(13))
 {
   Serial.println("sr.ttcswitch(13)");
 }
 if(sr.ttcSwitch(6))
 {
   Serial.println("sr.ttcswitch(13)");
 }
 if(sr.ttcSwitch(7))
 {
   Serial.println("sr.ttcswitch(13)");
 }
}
