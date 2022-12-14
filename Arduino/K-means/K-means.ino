#include "centerpoints.h"

int checker = 0;
int Distance[] = {0,0,0,0};


void setup() {
  
  Serial.begin(9600);
  pinMode(2, INPUT);
  
}

void loop() {

    int NumberOfMeasurements = 0;
    int Position = 0;
    Serial.println("Give number how many measurements");
    while(NumberOfMeasurements==0)
    {
     if(Serial.available()>0)
      {
         NumberOfMeasurements = Serial.parseInt();
      }
   }
   Serial.println("Give Arduino Position");
   while(Position==0)
    {
     if(Serial.available()>0)
      {
         Position = Serial.parseInt();
      }
   }
    for(int y = 0; y < NumberOfMeasurements; y++)
        {
        int minVal = 1000;

        Serial.print(Position);
        Serial.print("  ");
        

        int X = analogRead(A0);
        int Y = analogRead(A1);
        int Z = analogRead(A2);

        /*
        Serial.print(" X = ");
        Serial.print(X);

        Serial.print(" Y = ");
        Serial.print(Y);

        Serial.print(" Z = ");
        Serial.println(Z);

        */

        Distance[0] = sqrt(pow((X - kp[0][0]), 2) + pow((Y - kp[0][1]), 2) + pow((Z - kp[0][2]), 2));
        Distance[1] = sqrt(pow((X - kp[1][0]), 2) + pow((Y - kp[1][1]), 2) + pow((Z - kp[1][2]), 2));
        Distance[2] = sqrt(pow((X - kp[2][0]), 2) + pow((Y - kp[2][1]), 2) + pow((Z - kp[2][2]), 2));
        Distance[3] = sqrt(pow((X - kp[3][0]), 2) + pow((Y - kp[3][1]), 2) + pow((Z - kp[3][2]), 2));

        /*
        Serial.print(" Distance1 = ");
        Serial.println(Distance[0]);
        Serial.print(" Distance2 = ");
        Serial.println(Distance[1]);
        Serial.print(" Distance3 = ");
        Serial.println(Distance[2]);
        Serial.print(" Distance4 = ");
        Serial.println(Distance[3]);
        */

        for(int i = 0; i < 4; i++){
          if (Distance[i] < minVal) {
            minVal = Distance[i];
          }
        }

        /*
        if(minVal == Distance[0]){Serial.println("Arduino is up");}
        if(minVal == Distance[1]){Serial.println("Arduino is down");}
        if(minVal == Distance[2]){Serial.println("Arduino is left");}
        if(minVal == Distance[3]){Serial.println("Arduino is right");}
        */

        if(minVal == Distance[0]){Serial.println("1");}
        if(minVal == Distance[1]){Serial.println("2");}
        if(minVal == Distance[2]){Serial.println("3");}
        if(minVal == Distance[3]){Serial.println("4");}
        
        delay(500);
        }
}
