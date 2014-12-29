#include "LEDmodule5050.h"

uint8_t pins[] = {11,12,2,3,4,5,6,7};
FullColorLedModule Leds(8,9,10,8,pins);

void setup()
{
  Serial.begin(9600);
  
  pinMode(13,OUTPUT);
  
  delay(300);
  Leds.Dump();
  Leds.Setup();
}


void loop()
{
  Leds.On(FullColorLedModule::_White,(uint8_t)0);
  Leds.On(FullColorLedModule::_Blue,1);
  Leds.On(FullColorLedModule::_Red,2);
  Leds.On(FullColorLedModule::_Green,3);
  Leds.On(FullColorLedModule::_Purple,4);
  Leds.On(FullColorLedModule::_Margenta,5);
  Leds.On(0x000ffff00,6);
  
  Leds.On(0x00FF00,7);
  
  
  color c[7]= {  FullColorLedModule::_White,FullColorLedModule::_Blue,FullColorLedModule::_Red,
                 FullColorLedModule::_Green,FullColorLedModule::_Purple,FullColorLedModule::_Margenta,
                 FullColorLedModule::_Black
               };
  /*
  for(int cl=0; cl<7;cl++)
    for(int l=0; l<8;l++)
    {
      Leds.On(c[cl],(uint8_t) l);
      delay(100);
    }

  for(int cl=0; cl<7;cl++)
    for(int l=0; l<8;l++)
    {
      Leds.On(c[cl],(uint8_t) 7-l);
      delay(50);
    }

*/
  
   for(int i=0; i<20;i++)
  {
    Leds.On(FullColorLedModule::_Green,0);
    delay(100);
    Leds.On(FullColorLedModule::_Red,1);
    delay(100);
    for(int j=2;j<8;j++)
    {
      Leds.Off(j-2);
      if((j%2)==0)
        Leds.On(FullColorLedModule::_Green,j);
       else      
        Leds.On(FullColorLedModule::_Red,j);
      delay(100);
    }
    Leds.Off(6);
    delay(100);
    Leds.Off(7);
    delay(100);
  }

for(int i=0; i< 20;i++)
  {
     Leds.On(FullColorLedModule::_Red,0);
     delay(100);
     Leds.On(FullColorLedModule::_Red,1);
     Leds.On(FullColorLedModule::_Green,0);
     delay(100);
     for(int j=0;j<6;j++)
     {   
       Leds.Off(j);
       Leds.On(FullColorLedModule::_Green,j+1);
       Leds.On(FullColorLedModule::_Red,j+2);
       delay(100);
     }
     Leds.Off(6);
     Leds.On(FullColorLedModule::_Green,7);
     delay(100);
     Leds.Off(7);
  } 
  
  for(int i=0; i< 20;i++)
  {
    for(int l=0; l<8;l++)
    {
      Leds.On(FullColorLedModule::_Blue,l);
      Leds.On(FullColorLedModule::_Green,7-l);
      delay(50);
      Leds.Off(l);
      Leds.Off(7-l);
    }
    for(int l=0; l<8;l++)
    {
      Leds.On(FullColorLedModule::_Red,l);
      Leds.On(FullColorLedModule::_Purple,7-l);
      delay(50);
    }
    
    for(int l=0; l<4;l++)
    {
      Leds.Off(7-l);
      Leds.Off(l);
      delay(50);
    }
    for(int l=0; l<8;l++)
    {
      Leds.On(FullColorLedModule::_Red,l);
      Leds.On(FullColorLedModule::_Red,7-l);
      delay(50);
      Leds.Off(l);
      Leds.Off(7-l);

    }
    for(int l=0; l<4;l++)
    {
      Leds.On(FullColorLedModule::_Purple,3-l);
      Leds.On(FullColorLedModule::_Purple,4+l);
      delay(50);
      Leds.Off(3-l);
      Leds.Off(4+l);
    }
    for(int l=0; l<4;l++)
    {
      Leds.On(FullColorLedModule::_Green,3-l);
      Leds.On(FullColorLedModule::_Green,4+l);
      delay(50);
    }
  }
  for(int i=0; i< 20;i++)
  {
    for(int l=0; l<8;l++)
    {
      Leds.On(FullColorLedModule::_Blue,l);
      delay(50);
      Leds.Off(l);
    }
    for(int l=0; l<8;l++)
    {
      Leds.On(FullColorLedModule::_Green,7-l);
      delay(50);
      Leds.Off(7-l);
    }
    for(int l=0; l<8;l++)
    {
      Leds.On(FullColorLedModule::_Red,l);
      delay(50);
      Leds.Off(l);
    }
    for(int l=0; l<8;l++)
    {
      Leds.On(FullColorLedModule::_Purple,7-l);
      delay(50);
      Leds.Off(7-l);
    }
    for(int l=0; l<8;l++)
    {
      Leds.On(FullColorLedModule::_Red,l);
      delay(50);
      Leds.Off(l);
    }
    for(int l=0; l<8;l++)
    {
      Leds.On(FullColorLedModule::_Purple,7-l);
      delay(50);
      Leds.Off(7-l);
    }
  }
  
  uint8_t lds1[4] = {0,2,4,6};
  uint8_t lds2[4] = {1,3,5,7};
  uint8_t lds3[4] = {0,1,2,3};
  uint8_t lds4[4] = {4,5,6,7};

  for(int i=0; i< 20;i++)
  {
    Leds.On(FullColorLedModule::_Blue,4,lds1);
    delay(100);    
    Leds.Off(4,lds1);
    Leds.On(FullColorLedModule::_Blue,4,lds2);
    delay(100);    
    Leds.Off(4,lds2);
  }
  for(int i=0; i< 20;i++)
  {
    Leds.On(FullColorLedModule::_Blue,4,lds1);
    delay(100);    
    Leds.Off(4,lds1);
    Leds.On(FullColorLedModule::_Green,4,lds2);
    delay(100);    
    Leds.Off(4,lds2);
  }
  for(int i=0; i< 20;i++)
  {
    Leds.On(FullColorLedModule::_Red,4,lds1);
    delay(100);    
    Leds.Off(4,lds1);
    Leds.On(FullColorLedModule::_Green,4,lds2);
    delay(100);    
    Leds.Off(4,lds2);
  }
  for(int i=0; i< 20;i++)
  {
    Leds.On(FullColorLedModule::_Red,4,lds1);
    delay(100);  
    Leds.Off(4,lds1);  
    Leds.On(FullColorLedModule::_Purple,4,lds2);
    delay(100);    
    Leds.Off(4,lds2);
  }

  for(int i=0; i< 20;i++)
  {
    Leds.On(FullColorLedModule::_Red,4,lds3);
    delay(100);    
    Leds.Off(4,lds3);
    Leds.On(FullColorLedModule::_Purple,4,lds4);
    delay(100);    
    Leds.Off(4,lds4);
  }

  for(int i=0; i< 20;i++)
  {
    Leds.On(FullColorLedModule::_White,4,lds3);
    delay(100);    
    Leds.Off(4,lds3);
    Leds.On(FullColorLedModule::_Margenta,4,lds4);
    delay(100);    
    Leds.Off(4,lds4);
  }

  for(int i=0; i< 20;i++)
  {
    Leds.On(FullColorLedModule::_Red,4,lds1);
    delay(100);
    Leds.On(FullColorLedModule::_Margenta,4,lds1);
    Leds.On(FullColorLedModule::_Purple,4,lds2);
    delay(100);
    Leds.On(FullColorLedModule::_Blue,4,lds2);
  }

  for(int i=0; i< 20;i++)
  {
    Leds.On(FullColorLedModule::_Red,4,lds1);
    delay(100);    
    Leds.On(FullColorLedModule::_Purple,4,lds2);
    delay(100);    
    Leds.On(FullColorLedModule::_Red,4,lds1);
    delay(100);
    Leds.On(FullColorLedModule::_Margenta,4,lds2);
    delay(100);
    Leds.On(FullColorLedModule::_Green,4,lds2);
    Leds.On(FullColorLedModule::_Green,4,lds1);
    delay(100);
    Leds.On(FullColorLedModule::_Blue,4,lds2);
    Leds.On(FullColorLedModule::_Green,4,lds1);
    delay(100);
  }
    
 
}
