#include <Arduino.h>
#include "resources.h"
#include "modes.h"

Mode::Mode() {
}

MTest m_test = MTest();

void MTest::enter() {
  matrix.draw3x5Digit(7, 1, 1, matrix.Color(255,255,0));
  matrix.show();
}
Mode* MTest::loop() {
  return NULL;
}