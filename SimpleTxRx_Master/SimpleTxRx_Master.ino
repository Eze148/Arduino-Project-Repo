
/* YourDuinoStarter Example: Simple nRF24L01 Transmit
  - WHAT IT DOES: Transmits simple fixed data with nRF24L01 radio
  - SEE the comments after "//" on each line below
   Start with radios about 4 feet apart.
  - SEE the comments after "//" on each line below
  - CONNECTIONS: nRF24L01 Modules See:
  http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
  Uses the RF24 Library by TMRH2o here:
  https://github.com/TMRh20/RF24

  Arduino Nano V3.0 pinout:
   1 - GND 
   2 - VCC 3.3V !!! NOT 5V 
   3 - CE to Arduino pin 9 
   4 - CSN to Arduino pin 10 
   5 - SCK to Arduino pin 13 
   6 - MOSI to Arduino pin 11 
   7 - MISO to Arduino pin 12 
   8 - UNUSED 

   V1.02 02/06/2016
   Questions: terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <SPI.h>   // Comes with Arduino IDE
#include "RF24.h"  // Download and Install (See above)

/*-----( Declare Constants and Pin Numbers )-----*/ 
const int CE_Pin = 9; // Declare CE (Chip Enable) to pin 9
const int CSN_Pin = 10; // Declare CSN (Chip Select) to pin 10 
//None yet 
#define echoPin 6
#define trigPin 7
long distance, duration;
/*-----( Declare objects )-----*/ 
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 0;
// (Create an instance of a radio, specifying the CE and CS pins. ) 
RF24 myRadio (CE_Pin, CSN_Pin); // "myRadio" is the identifier you will use in following methods 

/*-----( Declare Variables )-----*/
byte addresses[][6] = {"Node1", "Node2"}; // Create address for 1 pipe.
int dataTransmitted;  // Data that will be Transmitted from the transmitter

void setup()   /****** SETUP: RUNS ONCE ******/
{
  // Use the serial Monitor (Symbol on far right). Set speed to 115200 (Bottom Right)
  Serial.begin(115200); 
  pinMode(echoPin, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);
  Serial.println(F("RF24/Simple Transmit data Test")); 
  Serial.println(F("Questions: terry@yourduino.com")); 

  /*-----------------( Setup nRF24L01 )--------------*/
  dataTransmitted = 100; // Arbitrary known data to transmit. Change it to test... 
  myRadio.begin();  // Start up the physical nRF24L01 Radio 
  myRadio.setCRCLength(RF24_CRC_8); // Options: 8, 16
  myRadio.setDataRate(RF24_250KBPS); // Options: 250KBPS, 1MBPS, 2MBPS
  myRadio.setChannel(108);  // Above most Wifi Channels 
  myRadio.setPALevel(RF24_PA_MAX); // Set the PA Level low to prevent power supply related issues since this is a getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default. 
  //  myRadio.setPALevel(RF24_PA_MAX);  // Uncomment for more power 
  //myRadio.setRetries(10,10); // Set minimum time for 10 retries.
  myRadio.openWritingPipe(addresses[0]); // Use the first entry in array 'addresses' (Only 1 right now) 
  myRadio.openReadingPipe(1, addresses[1]); 
  myRadio.startListening(); 
}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  myRadio.stopListening();
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) * 0.0343;
  //dataTransmitted = dataTransmitted + 1;  // Send different data next time
  myRadio.write(&distance, sizeof(distance)); //  Transmit the data

  Serial.print(F("Data Transmitted = "));
  Serial.print(distance);
  Serial.println(F(" No Acknowledge expected"));
  delay(1000);

}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/


//*********( THE END )***********

