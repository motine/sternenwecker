#include <Arduino.h>
#include "resources.h"
#include "modes.h"

Mode::Mode() {
}

MTest m_test = MTest();

uint8_t counter = 5;

void MTest::enter() {
}

Mode* MTest::loop() {
  matrix.draw3x5Digit(counter % 10, 1, 1, matrix.Color(255,0,0));
  matrix.show();
  return NULL;
}

Mode* MTest::press() {
  counter--;
  return NULL;
}
Mode* MTest::longpress() {
  counter++;
  return NULL;
}

Mode* MTest::left_turn() {
  counter--;
  return NULL;
}
Mode* MTest::right_turn() {
  counter++;
  return NULL;
}
