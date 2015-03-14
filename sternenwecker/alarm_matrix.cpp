#include "alarm_matrix.h"

AlarmMatrix::AlarmMatrix(uint8_t pin, uint8_t width, uint8_t height):
  Adafruit_NeoPixel(64, pin, NEO_GRB + NEO_KHZ800), width(width), height(height), count(width*height) {};


void AlarmMatrix::fillScreen(uint32_t color) {
  for (uint8_t i=0; i < count; i++) {
    setPixelColor(i, color);
  }
}

void AlarmMatrix::drawBitmap(uint8_t origin_x, uint8_t origin_y, const uint8_t bitmap[], uint8_t width, uint8_t height, uint32_t color) {
  // use setPixelColor to save time
  uint32_t black = Color(0,0,0); // color for pixels which are set to 0 in the bitmap
  for (uint8_t j=0; j < height; j++) {
    for (uint8_t i=0; i < width; i++) {
      drawPixel(origin_x+i, origin_y+j, ((pgm_read_byte(bitmap+j) >> (7-i)) & 1) ? color : black);
    }
  }
}

void AlarmMatrix::draw3x5Digit(uint8_t no, uint8_t x, uint8_t y, uint32_t color) {
  drawBitmap(x, y, FONT_3x5[no], 3, 5, color);
}

void AlarmMatrix::drawPixel(uint8_t x, uint8_t y, uint32_t color) {
  setPixelColor(y*width+x, color);
}