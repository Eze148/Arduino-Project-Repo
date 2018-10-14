#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(8);   
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.requestFrom(8, 1);
  while(Wire.available())
  {
    long c = Wire.read();
    Serial.print("Distance : ");
    Serial.print(c);
    Serial.println();
    delay(500);
  }
}


