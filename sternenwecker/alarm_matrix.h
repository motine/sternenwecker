#ifndef ALARM_MATRIX_H
#define ALARM_MATRIX_H

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <Adafruit_NeoPixel.h>

enum menu_icon_t {
  MenuIconSunset = 0,
  MenuIconSetAlarm = 1,
  MenuIconTorch = 2,
  MenuIconSetTime = 3
};

class AlarmMatrix : public Adafruit_NeoPixel {
  public:
    AlarmMatrix(uint8_t pin, uint8_t width, uint8_t height);

    void drawPixel(uint8_t x, uint8_t y, uint32_t color);
    uint32_t getPixel(uint8_t x, uint8_t y);
    void fillScreen(uint32_t color);
    void fillRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint32_t color);

    // bitmap is assumed to be a one-dimensional array of bytes.
    // Each of the bytes represents a row with the individual bits representing the values for the columns.
    // This makes a maximum of 8 pixels per column.
    // If the width is not 8, the bits will be read from left to right (MSB is left, LSB is right).
    void drawBitmap(uint8_t origin_x, uint8_t origin_y, const uint8_t bitmap[], uint8_t width, uint8_t height, uint32_t color);
    // same as drawBitmap, but overlap_color will be used if a overpainted pixel already has a color before drawing
    void addBitmap(uint8_t origin_x, uint8_t origin_y, const uint8_t bitmap[], uint8_t width, uint8_t height, uint32_t color, uint32_t overlap_color);
    // no may be between 0..9
    void draw3x5Digit(uint8_t no, uint8_t x, uint8_t y, uint32_t color);
    void displayMenuIcon(menu_icon_t menu_icon, uint32_t color);
    void displayConfirm(uint32_t color);
    void displayOff(uint32_t color);
    void displayTimeComponent(uint8_t number, bool dots_left, bool show_dots, uint32_t color);
    void displayDigitAndHand(uint8_t hour, uint8_t minute, uint32_t digit_color, uint32_t hand_color, uint32_t overlap_color);
    // converts a HSV to RGB values. For optimization we assume full S and full V.
    // hue is between 0 and 360.
    uint32_t hue_to_color(uint16_t hue);
    // saturation and value shall between 0.0 and 1.0
    uint32_t hsv_to_color(uint16_t hue, float saturation, float value);

    const uint8_t width;
    const uint8_t height;
    const uint8_t count;
};
#endif