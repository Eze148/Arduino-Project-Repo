#include <FastLED.h>

#define NUM_LEDS 150
#define LED_PIN 6
#define ANALOG_READ 7

CRGB leds[NUM_LEDS];
void setup() {
  Serial.begin(9600);
  //Set all lights to make sure all are working as expected
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}

void loop() {
  int sensor_value = analogRead(ANALOG_READ);

  int show_leds = map(sensor_value, 0, 1023, 0, 50);

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < show_leds) {
      leds[i] = CRGB(0, 255, 0);
    } else {
      leds[i] = CRGB(0, 0, 0);
    }
  }
  delay(5);
}

