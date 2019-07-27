/* This code works with MAX30102 + 128x32 OLED i2c + Buzzer and Arduino UNO
 * It's displays the Average BPM on the screen, with an animation and a buzzer sound
 * everytime a heart pulse is detected
 * It's a modified version of the HeartRate library example
 * Refer to www.surtrtech.com for more details or SurtrTech YouTube channel
 */
#define BLYNK_PRINT Serial
#include <BlynkSimpleSerialBLE.h>
#include <SoftwareSerial.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "F1N6ZqDRPRbbujwJZA5dRFKR6rbDa6zn";

SoftwareSerial SerialBLE(10, 11); // RX, TX

BlynkTimer timer;


#include <Wire.h>
#include "MAX30105.h"           //MAX3010x library
#include "heartRate.h"          //Heart rate calculating algorithm

MAX30105 particleSensor;


const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred
float beatsPerMinute;
int beatAvg;

void setup() {  
  Serial.begin(9600);

  SerialBLE.begin(9600);
  Blynk.begin(SerialBLE, auth);

  Serial.println("Waiting for connections...");

  // Setup a function to be called every second
  
  delay(3000);
  // Initialize sensor
  particleSensor.begin(Wire, I2C_SPEED_FAST); //Use default I2C port, 400kHz speed
  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  timer.setInterval(10L, myTimerEvent);
}

void myTimerEvent()
{
  long irValue = particleSensor.getIR();    //Reading the IR value it will permit us to know if there's a finger on the sensor or not
                                           //Also detecting a heartbeat
  if(irValue > 7000)
  {                                           //If a finger is detected
    if (checkForBeat(irValue) == true)                        //If a heart beat is detected
    {
      //Serial.println(beatAvg);
      Blynk.virtualWrite(V5, beatAvg); 
      if(beatAvg < 40 || beatAvg > 120)
      {
        Blynk.email("ezekielmarvin1998@gmail.com", "ALERT ERRATIC HEART RATE READING", "The current user heart rate is below 40 BPM! Please check on the current user and notify first responder.");
      }
      //tone(3,1000);                                        //And tone the buzzer for a 100ms you can reduce it it will be better
      //delay(100);
      //noTone(3);                                          //Deactivate the buzzer to have the effect of a "bip"
      //We sensed a beat!
      long delta = millis() - lastBeat;                   //Measure duration between two beats
      lastBeat = millis();

      beatsPerMinute = 60 / (delta / 1000.0);           //Calculating the BPM

      if (beatsPerMinute < 255 && beatsPerMinute > 20)               //To calculate the average we strore some values (4) then do some math to calculate the average
      {
        rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
        rateSpot %= RATE_SIZE; //Wrap variable

        //Take average of readings
        beatAvg = 0;
        for (byte x = 0 ; x < RATE_SIZE ; x++)
          beatAvg += rates[x];
        beatAvg /= RATE_SIZE;
      }
    }
  }
  if (irValue < 7000){       //If no finger is detected it inform the user and put the average BPM to 0 or it will be stored for the next measure
     beatAvg=0;
     Blynk.notify("Finger is not detected. Please hookup your finger to the sensor.");
     }
}

void loop() {
 Blynk.run();
 timer.run();
}
