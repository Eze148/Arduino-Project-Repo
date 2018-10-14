#include <SPI.h>
#include "RF24.h"

RF24 radio(9, 10);

const byte rxAddr[6] = "00001";

void setup()
{
  Serial.begin(115200);
  radio.begin();
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);  
  radio.stopListening();
}

void loop()
{
  const char text[] = "Hello World"; 
  radio.write(&text, sizeof(text));
  Serial.println(text);
  delay(1000);
  
}
