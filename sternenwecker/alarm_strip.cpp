#include "alarm_strip.h"

AlarmStrip::AlarmStrip(uint8_t width, uint8_t pin): width(width), Adafruit_NeoPixel(width, pin, NEO_GRB + NEO_KHZ800) {
};


void AlarmStrip::setup() {
  begin();
  clear();
  show();
}
// uint32_t AlarmStrip::hue_to_color(uint16_t hue) {
//   // for conversion for:
//   // - http://www.rapidtables.com/convert/color/hsv-to-rgb.htm
//   // - http://en.wikipedia.org/wiki/HSL_and_HSV#From_HSV
//   uint8_t h = hue / 60;
//   uint16_t x = 255*(1 - abs(fmod(hue / 60.0, 2.0) - 1));
//
//   switch (h) {
//     case 0:  return Color(255,   x,   0);
//     case 1:  return Color(  x, 255,  0);
//     case 2:  return Color(  0, 255,  x);
//     case 3:  return Color(  0,   x, 255);
//     case 4:  return Color(  x,   0, 255);
//     default: return Color(255,   0,  x);
//   }
// }
//
uint32_t AlarmStrip::hsv_to_color(uint16_t hue, float saturation, float value) {
  float h = hue / 60.0;
  float c = saturation * value;
  float x = c * (1.0 - fabs(fmod(h, 2.0) - 1.0));
  float m = value - c;
  uint8_t hi = h;
  uint8_t ci = c * 255;
  uint8_t xi = x * 255;
  uint8_t mi = m * 255;

  switch (hi) {
    case 0:  return Color(ci+mi, xi+mi,  0+mi);
    case 1:  return Color(xi+mi, ci+mi,  0+mi);
    case 2:  return Color( 0+mi, ci+mi, xi+mi);
    case 3:  return Color( 0+mi, xi+mi, ci+mi);
    case 4:  return Color(xi+mi,  0+mi, ci+mi);
    default: return Color(ci+mi,  0+mi, xi+mi);
  }
}

void AlarmStrip::fillScreen(uint32_t color) {
  for (uint8_t i=0; i < width; i++) {
    setPixelColor(i, color);
  }
}