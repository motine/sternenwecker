#include "alarm_matrix.h"

AlarmMatrix::AlarmMatrix(uint8_t pin):
  Adafruit_NeoMatrix(8, 8, pin, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE, NEO_GRB + NEO_KHZ800) {};


void AlarmMatrix::draw3x5Digit(uint8_t no, uint8_t x, uint8_t y, uint16_t color) {
  drawBitmap(x, y, FONT_3x5[no], 3, 5, color);
}