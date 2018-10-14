#include <FastLED.h>

#define NUM_LEDS 100
#define LED_PIN 9
int sensor = 7;
int i = 0;
CRGB leds[NUM_LEDS];

void setup(){
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
    FastLED.show();
  }
  
  pinMode(sensor, INPUT);
}

void loop(){
   boolean soundstate = digitalRead(7);
   Serial.println(soundstate);
   if(soundstate == 1)
   {
      leds[i]=CRGB::Red;
      FastLED.show();
      i++;
   }
   else if(soundstate == 0)
   {
      if(i<=0)
      {
        
      }
      else
      {
        leds[i]=CRGB::Black;
        FastLED.show();
        i--;
      }
   }
}

