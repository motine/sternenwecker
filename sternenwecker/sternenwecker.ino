#include <Adafruit_NeoPixel.h>
#include "modes.h"
#include "resources.h"

void setup() {
  Serial.begin(9600);
  setup_resources();
}

void loop() {
  loop_resources();
}