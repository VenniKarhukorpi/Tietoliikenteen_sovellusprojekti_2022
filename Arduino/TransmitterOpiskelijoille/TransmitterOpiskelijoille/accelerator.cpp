#include "accelerator.h"
#include <arduino.h>

Accelerator::Accelerator()
{
   Serial.println("Accelerator created!");
}


Accelerator::~Accelerator()
{
   Serial.println("Accelerator deleted!");
}

void Accelerator::makeMeasurement()
{
  Measurement m = {analogRead(A0), analogRead(A1), analogRead(A2)};
}
Measurement Accelerator::getMeasurement()
{
  retur Measurement m;
}
