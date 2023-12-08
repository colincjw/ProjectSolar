// #ProjectSolar Sun Measuring Box
// by Colin Chan

// Computational Practices 2 | FA'23

// Configuration | FastLED
#include <FastLED.h>  // header file
#define NUM_LEDS 25   // number of led present in your strip
#define DATA_PIN 11   // digital pin of your arduino

CRGB leds[NUM_LEDS];

// Reserve PINs for Functions
const int uvSensorPin = A5;  // select the input pin for the potentiometer

// Program Variables
unsigned long solarUpdateTime;  // Think this time as the pre-code time
unsigned long ledBlinkTime;     // Think this time as the pre-code time
unsigned long currentTime;      // Think this time as the during-code time
bool ledBlink = false;

const float uvChargeTime = 1;               // Default: 1-min to charge.
const float uvDischargeTime = 3;            // Default: 3-min to fully discharge.
const float solarInterval = 333.3333333;  // Default: 0.3 second interval for scanning UV from sensor.

const float uvGainRate = 1;
const float uvMaxValue = uvGainRate * (uvChargeTime * 60 * 1000) / solarInterval;
const float uvDropRate = uvChargeTime / uvDischargeTime * uvGainRate;


// Exponential Moving Average Filter
#define MAJOR_VALUE 0.95
float currentAverage;
float lastAverage;

// Measure values from sensors
float uvValue;                       // variable to store the value coming from the sensor
float solarValue;                    // variable for "solar"
int solarBracket = uvMaxValue / 10;  // 10-Bars of LEDs

void setup() {
  Serial.begin(115200);
  Serial.println("Project Solar Initialized");

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // Config: FastLED
  for (int i = 0; i < NUM_LEDS; i++) {                  // Config: FastLED – On start, set all dark
    leds[i] = CRGB::Black;
    FastLED.show();
  }

  // declare the uvReadLight as an OUTPUT:
  pinMode(uvReadLight, OUTPUT);
  pinMode(uvSensorPin, INPUT);
}

void updateSolar(float c) {
  if (c > 50 && solarValue < uvMaxValue) {
    solarValue += uvGainRate;
  } else if (solarValue > 0) {
    solarValue -= uvDropRate;
  }

  if (solarValue < 0) {
    solarValue = 0;
  }
}

void ledOn(int a) {
  leds[a * 2] = CRGB::Yellow;
  leds[a * 2 + 1] = CRGB::Yellow;
  FastLED.show();
}

void ledRed(int a) {
  leds[a * 2] = CRGB::Red;
  leds[a * 2 + 1] = CRGB::Red;
  FastLED.show();
}

void ledOff(int a) {
  leds[a * 2] = CRGB::Black;
  leds[a * 2 + 1] = CRGB::Black;
  FastLED.show();
}

void loop() {
  currentTime = millis();  // Get current time

  // read the value from the sensor:
  uvValue = analogRead(uvSensorPin);

  currentAverage = (MAJOR_VALUE * lastAverage) + ((1.0 - MAJOR_VALUE) * uvValue);
  lastAverage = currentAverage;

  if (currentTime - solarUpdateTime >= solarInterval) {
    updateSolar(currentAverage);
    solarUpdateTime = currentTime;  // Reset pre-code time to current (now) or during
  }

  if (currentTime - ledBlinkTime >= solarInterval * 2) {
    // Correlate solarValue to LED
    if (solarValue == 0) {
      if (!ledBlink) {
        ledRed(0);
        ledBlink = true;
      } else {
        ledOff(0);
        ledBlink = false;
      }
      for (int i = 20; i < NUM_LEDS; i++) {  // Config: FastLED – On start, set all dark
        leds[i] = CRGB::Black;
        FastLED.show();
      }
    } else {
      for (int i = 0; i < 10; i++) {            // SolarValue Brackets
        if (solarValue > (solarBracket * i)) {  // Interval 1
          ledOn(i);
        } else {
          ledOff(i);
        }
      }

      for (int i = 20; i < NUM_LEDS; i++) {  // Config: FastLED – On start, set all dark
        leds[i] = CRGB::Yellow;
        FastLED.show();
      }
    }

    ledBlinkTime = currentTime;  // Reset pre-code time to current (now) or during

    Serial.print("UV Value: ");
    Serial.println(uvValue);
    Serial.print("solarValue: ");
    Serial.println(solarValue);
  }

  char c = Serial.read();
  if (c == 't') {
    solarValue = 3;
  }
  if (c == 'a') {
    solarValue = uvMaxValue;
  }
  if (c == 'z') {
    solarValue = 0;
  }
}
