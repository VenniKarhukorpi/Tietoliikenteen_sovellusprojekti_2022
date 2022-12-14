#include "accelerator.h"
#include <arduino.h>

Measurement M;

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
  M = {analogRead(A0), analogRead(A1), analogRead(A2)};
  Serial.println(analogRead(A0));
  Serial.println(analogRead(A1));
  Serial.println(analogRead(A2));
}
Measurement Accelerator::getMeasurement()
{
  return M;
}
