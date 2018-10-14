#include <FirebaseArduino.h>
#include "ESP8266WiFi.h"

#define FIREBASE_HOST "altosmart-1398b.firebaseio.com"

const char* ssid = "Prasmul 2";
const char* password = "prasmul2018";
#define trigPin1 D1
#define echoPin1 D0
#define trigPin2 D3
#define echoPin2 D2
#define trigPin3 D6
#define echoPin3 D5

long duration1, distance1, duration2, distance2, duration3, distance3;
void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT_PULLUP);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT_PULLUP);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT_PULLUP);
  Serial.begin (115200);
  WiFi.begin(ssid, password);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected");
  Serial.println();
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST);
    
}

void loop() {
  digitalWrite(trigPin1, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin1, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1/2) / 29.1;
    
  if(distance1 <= 10)
  {
    Firebase.setInt("Sensor 3", 1);
  }
  else
  {
    Firebase.setInt("Sensor 3", 0);
  }
    Serial.println("Distance 3: ");
    Serial.print(distance1);
    Serial.println(" cm");
    delay(50);
  digitalWrite(trigPin2, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin2, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2/2) / 29.1;
  
  if(distance2 <= 10)
  {
    Firebase.setInt("Sensor 2", 1);
  }
  else
  {
    Firebase.setInt("Sensor 2", 0);
  }
    Serial.println("Distance 2: ");
    Serial.print(distance2);
    Serial.println(" cm");
    delay(50);
  digitalWrite(trigPin3, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin3, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = (duration3/2) / 29.1;
  
  if(distance3 <= 10)
  {
    Firebase.setInt("Sensor 1", 1);
  }
  else
  {
    Firebase.setInt("Sensor 1", 0);
  }
    Serial.println("Distance 1: ");
    Serial.print(distance3);
    Serial.println(" cm");
  delay(500);
} 

