#include "messaging.h"
#include "accelerator.h"

void setup() 
{
  Serial.begin(9600);
}

void loop()
{
  Accelerator Aobject;
  Messaging Mobject;
  uint8_t flags = 0;
  Serial.println("Give number how many measurements");
  int NumberOfMeasurements = 0;
  while(NumberOfMeasurements==0)
  {
    if(Serial.available()>0)
    {
       NumberOfMeasurements = Serial.parseInt();
    }
  }

  Serial.println("Which way is the sensor 1=up 2=down 3=left 4=right");
  int SensorDirection = 0;
  while(SensorDirection==0)
  {
    if(Serial.available()>0)
    {
       SensorDirection = Serial.parseInt();
    }
  }

  switch (SensorDirection) {
    case 1:
      flags=0x01;
      break;
    case 2:
      flags=0x02;
      break;
    case 3:
      flags=0x03;
      break;
    case 4:
      flags=0x04;   
  }
  
  for(int M = 0;M<NumberOfMeasurements;M++)
  {
     Aobject.makeMeasurement();
     Measurement m = Aobject.getMeasurement();   
     uint8_t id = M;
  /*
  Serial.println("Which way is the sensor 1=up 2=down 3=left 4=right");
  int SensorDirection = 0;
  while(SensorDirection==0)
  {
    if(Serial.available()>0)
    {
       SensorDirection = Serial.parseInt();
    }
  }

  switch (SensorDirection) {
    case 1:
      flags=0x01;
      break;
    case 2:
      flags=0x02;
      break;
    case 3:
      flags=0x03;
      break;
    case 4:
      flags=0x04;   
  }
   */  
     Serial.println(flags);
     Mobject.createMessage(m);
     if(Mobject.sendMessage(id,flags))
     {
       Serial.println("Successfull transmission");
     }
     else
     {
       Serial.println("Transmission fails");
     }
     if(Mobject.receiveACK())
     {
       Serial.println("Receiver got message, going to next measurement");
     }
     else
     {
       Serial.println("Reciver did not get the message. Need to resend it");
       M--;  // Let's just revind for loop
     }
  } // end of for
}   // end of loop
