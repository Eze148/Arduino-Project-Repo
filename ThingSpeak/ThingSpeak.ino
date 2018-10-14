#include "ThingSpeak.h"
#include <SPI.h>
#include <Ethernet.h>
//#include "EmonLib.h"

//EnergyMonitor emon1;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
EthernetClient client;
// On Arduino:  0 - 1023 maps to 0 - 5 volts
//#define VOLTAGE_MAX 5.0
//#define VOLTAGE_MAXCOUNTS 1023.0

unsigned long myChannelNumber = 592825;               //Channel ID from ThingSpeak
const char * myWriteAPIKey = "HR5YZT72V4TBG6NH";      //Write API Key Derived from ThingSpeak

void setup()
{
  Serial.begin(9600);
  //emon1.current(1, 111.1);
  Ethernet.begin(mac);
  ThingSpeak.begin(client);
}

void loop()
{
  int r = rand();
  //float Irms = emon1.calcIrms(1480);
  Serial.print("Number: ");
  Serial.println(r);
  Serial.println();

  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  ThingSpeak.writeField(myChannelNumber, 1, r, myWriteAPIKey);
  delay(20000); // ThingSpeak will only accept updates every 15 seconds.
}


