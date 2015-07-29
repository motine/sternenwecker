#ifndef ALARM_STRIP_H
#define ALARM_STRIP_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class AlarmStrip : public Adafruit_NeoPixel {
  public:
    AlarmStrip(uint8_t width, uint8_t pin);
    void setup();
    uint32_t hsv_to_color(uint16_t hue, float saturation, float value);
    void fillScreen(uint32_t color);
  protected:
    uint8_t width;
};
#endif