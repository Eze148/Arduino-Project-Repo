#include <Wire.h>
#define echoPin D3
#define trigPin D4
long duration, distance;
void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT_PULLUP);
  Wire.begin(D1, D2);
  Wire.onRequest(requestEvent);
  Serial.begin(115200); 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) * 0.0343;  
  Serial.print(distance);
  Serial.println();
  delay(1000);
}

void requestEvent()
{
  Wire.write(distance);
}

