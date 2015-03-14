#include "alarm_matrix.h"

AlarmMatrix::AlarmMatrix(uint8_t pin, uint8_t led_count):
  Adafruit_NeoPixel(64, pin, NEO_GRB + NEO_KHZ800), led_count(led_count) {};


void AlarmMatrix::fillScreen(uint32_t color) {
  for (uint8_t i=0; i < led_count; i++) {
    setPixelColor(i, color);
  }
  show();
}


void AlarmMatrix::draw3x5Digit(uint8_t no, uint8_t x, uint8_t y, uint16_t color) {
  // drawBitmap(x, y, FONT_3x5[no], 3, 5, color);
  // TODO implement drawBitmap
}