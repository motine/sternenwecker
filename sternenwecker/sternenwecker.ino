#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <RTClib.h>
#include "modes.h"
#include "display_test.h"
#include "resources.h"

void setup() {
  Serial.begin(9600);
  setup_resources();
}

void loop() {
  loop_resources();
}