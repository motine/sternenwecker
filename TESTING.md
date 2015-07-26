# Testing

To test your components, here some test programs.
Put them in a sketch and put them on your Adruino. Please see the `README.md` for more details.

## Strip

```c
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel matrix = Adafruit_NeoPixel(60, 6, NEO_GRB + NEO_KHZ800);

void setup() {
  matrix.begin();
}


void loop() {
  matrix.clear();
  for (int i=0; i < 60; i++) {
    matrix.setPixelColor(i, 255,0,0);
    matrix.show();
    delay(50);
    matrix.setPixelColor(i, 10,10,10);
    matrix.show();
  }
}
```

## Matrix

```c
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

void setup() {
  matrix.begin(0x70);
}

void loop() {
  matrix.clear();
  for (uint8_t j=0; j < 8; j++) {
    for (uint8_t i=0; i < 8; i++) {
      matrix.drawPixel(j, i, LED_GREEN);
      matrix.writeDisplay();
      delay(80);
      matrix.drawPixel(j, i, LED_RED);
      matrix.writeDisplay();
    }
  }
}
```

## Clock Module (RTC)

```c
// Open the serial console to see the output.
// Don't forget to set the rate to 57600!

#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 RTC;

void setup () {
    Serial.begin(57600);
    Wire.begin();
    RTC.begin();
    RTC.adjust(DateTime(__DATE__, __TIME__));
}

void loop () {
    DateTime now = RTC.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    delay(3000);
}
```

## Encoder / Button

This is quite cumbersome to test this without having to copy my library. Hence, just run the main program `sternenwecker.ino` and see if it works.
If you made sure the matrix and the strip works, then the excoder must be broken.