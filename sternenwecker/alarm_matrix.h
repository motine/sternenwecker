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
     AlarmMatrix(uint8_t pin, uint8_t led_count);
     // no may be between 0..9
     void fillScreen(uint32_t color);
     void draw3x5Digit(uint8_t no, uint8_t x, uint8_t y, uint16_t color);
     
     const uint8_t led_count;
};