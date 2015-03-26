#include "alarm_matrix.h"

AlarmMatrix::AlarmMatrix(uint8_t pin, uint8_t width, uint8_t height):
  Adafruit_NeoPixel(width*height, pin, NEO_GRB + NEO_KHZ800), width(width), height(height), count(width*height) {
};

uint32_t AlarmMatrix::hue_to_color(uint16_t hue) {
  // for conversion for:
  // - http://www.rapidtables.com/convert/color/hsv-to-rgb.htm
  // - http://en.wikipedia.org/wiki/HSL_and_HSV#From_HSV
  uint8_t h = hue / 60;
  uint16_t x = 255*(1 - abs(fmod(hue / 60.0, 2.0) - 1));

  switch (h) {
    case 0:  return Color(255,   x,   0);
    case 1:  return Color(  x, 255,  0);
    case 2:  return Color(  0, 255,  x);
    case 3:  return Color(  0,   x, 255);
    case 4:  return Color(  x,   0, 255);
    default: return Color(255,   0,  x);
  }
}

void AlarmMatrix::fillScreen(uint32_t color) {
  for (uint8_t i=0; i < count; i++) {
    setPixelColor(i, color);
  }
}

void AlarmMatrix::fillRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint32_t color) {
  for (uint8_t j=y; j < y+height; j++) {
    for (uint8_t i=x; i < x+width; i++) {
      drawPixel(i, j, color);
    }
  }
}


void AlarmMatrix::drawBitmap(uint8_t origin_x, uint8_t origin_y, const uint8_t bitmap[], uint8_t width, uint8_t height, uint32_t color) {
  // use setPixelColor to save time
  for (uint8_t j=0; j < height; j++) {
    for (uint8_t i=0; i < width; i++) {
      if ((pgm_read_byte(bitmap+j) >> (7-i)) & 1)
        drawPixel(origin_x+i, origin_y+j, color);
    }
  }
}

void AlarmMatrix::draw3x5Digit(uint8_t no, uint8_t x, uint8_t y, uint32_t color) {
  drawBitmap(x, y, FONT_3x5[no], 3, 5, color);
}

void AlarmMatrix::drawPixel(uint8_t x, uint8_t y, uint32_t color) {
  if ((x >= width) || (x < 0) || (y >= height) || y < 0)
    return;
  setPixelColor(y*width+x, color);
}