#ifndef ALARM_MATRIX_H
#define ALARM_MATRIX_H

#include <Arduino.h>
#include <avr/pgmspace.h>
#include "Adafruit_LEDBackpack.h"

enum menu_icon_t {
  MenuIconSunset = 0,
  MenuIconSetAlarm = 1,
  MenuIconTorch = 2,
  MenuIconSetTime = 3
};

class AlarmMatrix : public Adafruit_BicolorMatrix {
  public:
    AlarmMatrix();

    // uint32_t getPixel(uint8_t x, uint8_t y);
    // void fillScreen(uint16_t color);

    // adds source on target by changing target. left, top, width and height work like the ones in drawBitmap.
    // target is assumed to be in non-pgm and source to be in pgm memory.
    void addBitmap(uint8_t target[], const uint8_t source[], uint8_t left, uint8_t top, uint8_t width, uint8_t height);
    // will draw a and b. If there are pixels set in both, overlap_color will be used.
    // a is assumed to be in non-pgm and b to be in pgm memory.
    void drawTwoBitmaps(const uint8_t a[], const uint8_t b[], uint16_t a_color, uint16_t b_color, uint16_t overlap_color);
    // no may be between 0..9
    // void draw3x5Digit(uint8_t no, uint8_t x, uint8_t y, uint16_t color);
    void displayMenuIcon(menu_icon_t menu_icon);
    void displayConfirm();
    void displayOff();
    void displayTimeComponent(uint8_t number, bool dots_left, bool show_dots);
    void displayDigitAndHand(uint8_t hour, uint8_t minute);
  };
#endif