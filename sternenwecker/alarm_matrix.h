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
    void fillScreen(uint16_t color);

    // // same as drawBitmap, but overlap_color will be used if a overpainted pixel already has a color before drawing
    void addBitmap(uint8_t origin_x, uint8_t origin_y, const uint8_t bitmap[], uint8_t width, uint8_t height, uint16_t color, uint16_t overlap_color);
    // no may be between 0..9
    void draw3x5Digit(uint8_t no, uint8_t x, uint8_t y, uint16_t color);
    void displayMenuIcon(menu_icon_t menu_icon);
    void displayConfirm();
    void displayOff();
    void displayTimeComponent(uint8_t number, bool dots_left, bool show_dots);
    void displayDigitAndHand(uint8_t hour, uint8_t minute);
  };
#endif