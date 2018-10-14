#define trigPin D2
#define echoPin D1
long distance, duration;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT_PULLUP);
  Serial.begin (115200);
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
    
    Serial.println("Distance : ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(1000);
}
