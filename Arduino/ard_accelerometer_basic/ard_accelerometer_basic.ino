/*
Tulosta numeroita ikiloopissa sarjaporttiin
*/
void setup()
{
  Serial.begin(9600); // sarjaportin nopeus
  Serial.print("Serial communication");
}

void loop()
{
  int X = analogRead(A0);
  int Y = analogRead(A1);
  int Z = analogRead(A2);

  Serial.print(" X = ");
  Serial.print(X);

  Serial.print(" Y = ");
  Serial.print(Y);

  Serial.print(" Z = ");
  Serial.println(Z);
 
  delay(500); // 0.5 s viive
}
