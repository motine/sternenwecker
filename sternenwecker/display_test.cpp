#include <Arduino.h>
#include "resources.h"
#include "display_test.h"

MDisplayTest m_display_test = MDisplayTest();

void MDisplayTest::enter() {
}
Mode* MDisplayTest::loop() {
  return NULL;
}
Mode* MDisplayTest::press() {
  return NULL;
}
Mode* MDisplayTest::longpress() {
  return &m_menu;
}
Mode* MDisplayTest::left_turn() {
  return NULL;
}
Mode* MDisplayTest::right_turn() {
  return NULL;
}