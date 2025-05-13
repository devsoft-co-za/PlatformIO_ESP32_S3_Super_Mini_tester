#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 36
#define DATA_PIN 8
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

#define CYLON_MODE

void cylonMulticolour()
{
  static uint8_t hue = 0;
  Serial.print("x");
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show();
    fadeall();
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
  Serial.print("x");
  for (int i = (NUM_LEDS)-1; i >= 0; i--)
  {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show();
    fadeall();
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
  yield();
}

void blinkLED()
{
  digitalWrite(DATA_PIN, HIGH);
  digitalWrite(CLOCK_PIN, HIGH);
  delay(500);
  digitalWrite(DATA_PIN, LOW);
  digitalWrite(CLOCK_PIN, LOW);
  delay(500);
}

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
  FastLED.setBrightness(20);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
}

void loop() {
#ifdef CYLON_MODE
  cylonMulticolour();
#else
  blinkLED();
#endif
}
