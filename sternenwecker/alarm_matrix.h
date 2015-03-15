#ifndef ALARM_MATRIX_H
#define ALARM_MATRIX_H

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <Adafruit_NeoPixel.h>

static const uint8_t PROGMEM
  FONT_3x5[10][5] =
  {
    { B11100000, // 0
      B10100000,
      B10100000,
      B10100000,
      B11100000 },
    { B01100000, // 1
      B00100000,
      B00100000,
      B00100000,
      B00100000 },
    { B11100000, // 2
      B00100000,
      B11100000,
      B10000000,
      B11100000 },
    { B11100000, // 3
      B00100000,
      B01100000,
      B00100000,
      B11100000 },
    { B10000000, // 4
      B10000000,
      B11100000,
      B01000000,
      B01000000 },
    { B11100000, // 5
      B10000000,
      B11100000,
      B00100000,
      B11100000 },
    { B10000000, // 6
      B10000000,
      B11100000,
      B10100000,
      B11100000 },
    { B11100000, // 7
      B00100000,
      B01100000,
      B01000000,
      B01000000 },
    { B11100000, // 8
      B10100000,
      B11100000,
      B10100000,
      B11100000 },
    { B11100000, // 9
      B10100000,
      B11100000,
      B00100000,
      B00100000 }
  };

class AlarmMatrix : public Adafruit_NeoPixel {
  public:
    AlarmMatrix(uint8_t pin, uint8_t width, uint8_t height);

    void drawPixel(uint8_t x, uint8_t y, uint32_t color);
    void fillScreen(uint32_t color);

    // bitmap is assumed to be a one-dimensional array of bytes.
    // Each of the bytes represents a row with the individual bits representing the values for the columns.
    // This makes a maximum of 8 pixels per column.
    // If the width is not 8, the bits will be read from left to right (MSB is left, LSB is right).
    void drawBitmap(uint8_t origin_x, uint8_t origin_y, const uint8_t bitmap[], uint8_t width, uint8_t height, uint32_t color);

    // no may be between 0..9
    void draw3x5Digit(uint8_t no, uint8_t x, uint8_t y, uint32_t color);

    // converts a HSV to RGB values. For optimization we assume full S and full V.
    // hue is between 0 and 360.
    uint32_t hue_to_rgb(uint16_t hue);

    const uint8_t width;
    const uint8_t height;
    const uint8_t count;
};
#endif