#include <Arduino.h>
#include "resources.h"
#include "modes.h"

Mode::Mode() {
}

MTest m_test = MTest();

uint8_t counter = 5;
uint8_t color_index = 0;
uint32_t color_left;
uint32_t color_right;

void update_colors() {
  switch (color_index % 6) {
  case 0:
    color_left = matrix.Color(255,0,0);
    color_right = matrix.Color(255,255,0);
    break;
  case 1:
    color_left = matrix.Color(255,0,255);
    color_right = matrix.Color(0,0,255);
    break;
  case 2:
    color_left = matrix.Color(0,255,0);
    color_right = matrix.Color(255,255,255);
    break;
  case 3:
    color_left = matrix.Color(255,0,0);
    color_right = matrix.Color(0,0,255);
    break;
  case 4:
    color_left = matrix.Color(255,255,0);
    color_right = matrix.Color(255,0,255);
    break;
  case 5:
    color_left = matrix.Color(255,255,0);
    color_right = matrix.Color(0,255,255);
    break;
  }
}

void MTest::enter() {
  update_colors();
}

Mode* MTest::loop() {
  matrix.draw3x5Digit((counter / 10) % 10, 1, 2, color_left);
  matrix.draw3x5Digit(counter % 10, 5, 2, color_right);
  matrix.show();
  return NULL;
}

Mode* MTest::press() {
  color_index++;
  update_colors();
  return NULL;
}
Mode* MTest::longpress() {
  color_index--;
  update_colors();
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
