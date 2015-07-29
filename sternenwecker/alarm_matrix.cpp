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

// void AlarmMatrix::fillScreen(uint16_t color) {
//   for (uint8_t j=0; j < 8; j++) {
//     for (uint8_t i=0; i < 8; i++) {
//       drawPixel(i, j, color);
//     }
//   }
// }

void AlarmMatrix::dim() {
  setBrightness(TIME_BRIGHTNESS_DIM);
}
void AlarmMatrix::undim() {
  setBrightness(TIME_BRIGHTNESS_FULL);  
}

void AlarmMatrix::addBitmap(uint8_t target[], const uint8_t source[], uint8_t left, uint8_t top, uint8_t width, uint8_t height) {
  for (uint8_t j = 0; j < height; j++) {
    for (uint8_t i = 0; i < width; i++) {
      target[j+top] = target[j+top] | ((pgm_read_byte(source + j) & (128 >> i)) >> left);
    }
  }
}

void AlarmMatrix::drawTwoBitmaps(const uint8_t a[], const uint8_t b[], uint16_t a_color, uint16_t b_color, uint16_t overlap_color) {
  uint8_t is_a = false;
  uint8_t is_b = false;
  for (uint8_t j = 0; j < 8; j++) {
    for (uint8_t i = 0; i < 8; i++) {
      is_a = a[j] & (128 >> i);
      is_b = pgm_read_byte(b + j) & (128 >> i);
      if (is_a && is_b) {
        drawPixel(i, j, overlap_color);
      } else {
        if (is_a)
          drawPixel(i, j, a_color);
        if (is_b)
          drawPixel(i, j, b_color);
      }
    }
  }
}

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
  clear();
  uint8_t num_x = (dots_left) ? 2 : 0;
  drawBitmap(num_x  , 2, FONT_3x5[number / 10], 3,5, LED_RED);
  drawBitmap(num_x+3, 2, FONT_3x5[number % 10], 3,5, LED_RED);

  if (show_dots) {
    uint8_t dots_x = (dots_left) ? 0 : 7;
    drawPixel(dots_x, 3, LED_YELLOW);
    drawPixel(dots_x, 5, LED_YELLOW);
  }
  writeDisplay();
}

void AlarmMatrix::displayDigitAndHand(uint8_t hour, uint8_t minute) {
  clear();
  uint8_t digits[8] = {0,0,0,0,0,0,0,0};
  if (hour < 10) {
    addBitmap(digits, FONT_3x5[hour % 10], 3, 2, 3,5);
  } else {
    addBitmap(digits, FONT_3x5[hour / 10], 1,2, 3,5);
    addBitmap(digits, FONT_3x5[hour % 10], 4,2, 3,5);
  }
  drawTwoBitmaps(digits, HAND_8_8x8[minute*8/60], LED_RED, LED_YELLOW, LED_YELLOW);
  writeDisplay();
}
