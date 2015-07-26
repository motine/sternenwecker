#include "alarm_matrix.h"

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

static const uint8_t PROGMEM 
  BITMAP_OFF[8] = {
      B00000000,
      B00000000,
      B00100100,
      B00011000,
      B00011000,
      B00100100,
      B00000000,
      B00000000 };

static const uint8_t PROGMEM 
  BITMAP_CONFIRM[8] = {
      B00000000,
      B00000000,
      B00000010,
      B00000100,
      B00101000,
      B00010000,
      B00000000,
      B00000000 };

static const uint8_t PROGMEM 
  HAND_8_8x8[8][8] = {
    { B00001000,
      B00001000,
      B00001000,
      B00001000,
      B00001000,
      B00000000,
      B00000000,
      B00000000 },
    { B00000000,
      B00000001,
      B00000010,
      B00000100,
      B00001000,
      B00000000,
      B00000000,
      B00000000 },
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00001111,
      B00000000,
      B00000000,
      B00000000 },
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00001000,
      B00000100,
      B00000010,
      B00000001 },
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00010000,
      B00010000,
      B00010000,
      B00010000 },
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00010000,
      B00100000,
      B01000000,
      B10000000 },
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B11110000,
      B00000000,
      B00000000,
      B00000000 },
    { B00000000,
      B10000000,
      B01000000,
      B00100000,
      B00010000,
      B00000000,
      B00000000,
      B00000000 }};

static const uint8_t PROGMEM 
  MENU_ICONS[4][8] = {
    { B00000000,
      B00000000,
      B00100000,
      B00010100,
      B00001100,
      B00011100,
      B00000000,
      B00000000 },
    { B00000000,
      B00000000,
      B00011100,
      B00001100,
      B00010100,
      B00100000,
      B00000000,
      B00000000 },
    { B00000000,
      B00000000,
      B00111100,
      B00111100,
      B00111100,
      B00111100,
      B00000000,
      B00000000 },
    { B00000000,
      B00011000,
      B00011000,
      B00011000,
      B00000000,
      B00011000,
      B00000000,
      B00000000 },
    };
    
AlarmMatrix::AlarmMatrix():
  Adafruit_BicolorMatrix() {
};

// uint32_t AlarmMatrix::hue_to_color(uint16_t hue) {
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
// uint32_t AlarmMatrix::hsv_to_color(uint16_t hue, float saturation, float value) {
//   float h = hue / 60.0;
//   float c = saturation * value;
//   float x = c * (1.0 - fabs(fmod(h, 2.0) - 1.0));
//   float m = value - c;
//   uint8_t hi = h;
//   uint8_t ci = c * 255;
//   uint8_t xi = x * 255;
//   uint8_t mi = m * 255;
//
//   switch (hi) {
//     case 0:  return Color(ci+mi, xi+mi,  0+mi);
//     case 1:  return Color(xi+mi, ci+mi,  0+mi);
//     case 2:  return Color( 0+mi, ci+mi, xi+mi);
//     case 3:  return Color( 0+mi, xi+mi, ci+mi);
//     case 4:  return Color(xi+mi,  0+mi, ci+mi);
//     default: return Color(ci+mi,  0+mi, xi+mi);
//   }
// }

void AlarmMatrix::fillScreen(uint16_t color) {
  for (uint8_t j=0; j < 8; j++) {
    for (uint8_t i=0; i < 8; i++) {
      drawPixel(i, j, color);
    }
  }
}

void AlarmMatrix::addBitmap(uint8_t origin_x, uint8_t origin_y, const uint8_t bitmap[], uint8_t width, uint8_t height, uint16_t color, uint16_t overlap_color) {
  // TODO
  drawBitmap(origin_x, origin_y, bitmap, width, height, color);
//   int16_t i, j, byteWidth = (w + 7) / 8;
//
//   for(j=0; j<h; j++) {
//     for(i=0; i<w; i++ ) {
//       if(pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) {
//         drawPixel(x+i, y+j, color);
//       }
//     }
//   }
// }  
  
//   // very similar to drawBitmap (refactor!)
//   for (uint8_t j=0; j < height; j++) {
//     for (uint8_t i=0; i < width; i++) {
//       if ((pgm_read_byte(bitmap+j) >> (7-i)) & 1) {
//         uint32_t c = color;
//         if (getPixel(origin_x+i, origin_y+j) > 0)
//           c = overlap_color;
//         drawPixel(origin_x+i, origin_y+j, c);
//       }
//     }
//   }
  writeDisplay();
}

void AlarmMatrix::draw3x5Digit(uint8_t no, uint8_t x, uint8_t y, uint16_t color) {
  drawBitmap(x, y, FONT_3x5[no], 3, 5, color);
  writeDisplay();
}

// uint32_t AlarmMatrix::getPixel(uint8_t x, uint8_t y) {
//   if ((x >= width) || (x < 0) || (y >= height) || y < 0)
//     return 0;
//   getPixelColor(y*width+x);
// }

void AlarmMatrix::displayMenuIcon(menu_icon_t menu_icon) {
  clear();
  drawBitmap(0, 0, MENU_ICONS[menu_icon], 8, 8, LED_GREEN);
  writeDisplay();
}

void AlarmMatrix::displayConfirm() {
  clear();
  drawBitmap(0,0, BITMAP_CONFIRM, 8,8, LED_GREEN);
  writeDisplay();
}
void AlarmMatrix::displayOff() {
  clear();
  drawBitmap(0,0, BITMAP_OFF, 8,8, LED_RED);
  writeDisplay();
}

void AlarmMatrix::displayTimeComponent(uint8_t number, bool dots_left, bool show_dots) {
  // TODO
  // clear();
  // uint8_t num_x = (dots_left) ? 2 : 0;
  // draw3x5Digit(number / 10, num_x, 2, color);
  // draw3x5Digit(number % 10, num_x+3, 2, color);
  // if (show_dots) {
  //   uint8_t dots_x = (dots_left) ? 0 : 7;
  //   drawPixel(dots_x, 3, color);
  //   drawPixel(dots_x, 5, color);
  // }
  // show();
}

void AlarmMatrix::displayDigitAndHand(uint8_t hour, uint8_t minute) {
  clear();
  if (hour < 10) {
    draw3x5Digit(hour % 10, 3, 2, LED_RED);
  } else {
    draw3x5Digit(hour / 10, 1, 2, LED_RED);
    draw3x5Digit(hour % 10, 4, 2, LED_RED);
  }
  addBitmap(0, 0, HAND_8_8x8[minute*8/60], 8, 8, LED_GREEN, LED_YELLOW);
  writeDisplay();
}
