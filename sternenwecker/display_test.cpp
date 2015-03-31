#include <Arduino.h>
#include "resources.h"
#include "display_test.h"

MDisplayTest m_display_test = MDisplayTest();
void MDisplayTest::enter() {
  enter_millis = millis();
  current_test = 0;
  hour = 5;
  min = 45;
}


static const uint8_t PROGMEM 
  HAND_4x4[12][4] = {
    { B00100000,
      B00100000,
      B00000000,
      B00000000 },
    { B00010000,
      B00100000,
      B00000000,
      B00000000 },
    { B00000000,
      B00110000,
      B00000000,
      B00000000 },
    { B00000000,
      B00000000,
      B00110000,
      B00000000 },
    { B00000000,
      B00000000,
      B00100000,
      B00010000 },
    { B00000000,
      B00000000,
      B00100000,
      B00100000 },
    { B00000000,
      B00000000,
      B01000000,
      B01000000 },
    { B00000000,
      B00000000,
      B01000000,
      B10000000 },
    { B00000000,
      B00000000,
      B11000000,
      B00000000 },
    { B00000000,
      B11000000,
      B00000000,
      B00000000 },
    { B10000000,
      B01000000,
      B00000000,
      B00000000 },
    { B01000000,
      B01000000,
      B00000000,
      B00000000 }};

static const uint8_t PROGMEM 
  HAND_20_8x8[20][8] = {
    { B00001000,
      B00001000,
      B00001000,
      B00001000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
    { B00000010,
      B00000100,
      B00000100,
      B00001000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
    { B00000001,
      B00000010,
      B00000100,
      B00001000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
    { B00000000,
      B00000001,
      B00000110,
      B00001000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
    { B00000000,
      B00000000,
      B00000000,
      B00001111,
      B00000000,
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
      B00000110,
      B00000001,
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
      B00001000,
      B00000100,
      B00000100,
      B00000010 },
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00001000,
      B00001000,
      B00001000,
      B00001000 },
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
      B00100000,
      B01000000 },
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
      B00010000,
      B01100000,
      B10000000,
      B00000000 },
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B11110000,
      B00000000,
      B00000000,
      B00000000 },
    { B00000000,
      B00000000,
      B00000000,
      B11110000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
    { B00000000,
      B10000000,
      B01100000,
      B00010000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
    { B10000000,
      B01000000,
      B00100000,
      B00010000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
    { B01000000,
      B00100000,
      B00100000,
      B00010000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
    { B00010000,
      B00010000,
      B00010000,
      B00010000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 }};

static const uint8_t PROGMEM 
  HAND_8_8x8[8][8] = {
    { B00001000,
      B00001000,
      B00001000,
      B00001000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
    { B00000001,
      B00000010,
      B00000100,
      B00001000,
      B00000000,
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
      B11110000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 },
    { B10000000,
      B01000000,
      B00100000,
      B00010000,
      B00000000,
      B00000000,
      B00000000,
      B00000000 }};


Mode* MDisplayTest::loop() {
  // uint32_t color1 = matrix.Color(30, 0, 0);
  uint32_t color1_dark = matrix.Color(5, 0, 0);
  // uint32_t color2 = matrix.Color(20,10, 0);
  uint32_t color3 = matrix.Color(15,15, 0);
  
  uint32_t background = matrix.Color(15, 0, 0);
  uint32_t color1 = matrix.Color(15,5, 0);
  uint32_t color2 = matrix.Color(15,5, 0);

  matrix.clear();
  matrix.fillScreen(background);
  
  if (current_test == 0) {
    matrix.clear();
    // this used to me in MTime
    uint8_t TIME_SCROLL_STEP_DURATION = 80;
    int8_t scroll_offset = 8 - (millis() - enter_millis) / TIME_SCROLL_STEP_DURATION;

    if (clock.current_hour < 10)
      scroll_offset-=4;

    if (scroll_offset < -24) { // use -18 if you want no pause between scrolls
      enter_millis = millis();
      // start again
    }

    if (clock.current_hour >= 10)
      matrix.draw3x5Digit(clock.current_hour / 10, scroll_offset, 2, color1);
    matrix.draw3x5Digit(clock.current_hour % 10, scroll_offset+4, 2, color1);
    matrix.drawPixel(scroll_offset+8, 3, color1);
    matrix.drawPixel(scroll_offset+8, 5, color1);
    matrix.draw3x5Digit(clock.current_minute / 10, scroll_offset+11, 2, color1);
    matrix.draw3x5Digit(clock.current_minute % 10, scroll_offset+15, 2, color1);
  }
  
  if (current_test == 1) {
    // one digit, 4x5 rectangle
    matrix.draw3x5Digit(hour % 10, 0, 2, color1);
    uint32_t c;
    uint8_t OFFSET_LEFT = 4;
    uint8_t OFFSET_TOP = 2;
    for (uint8_t i=0; i < 20; i++) {
      c = (min > i*3) ? color1 : color1_dark;
      matrix.drawPixel(OFFSET_LEFT + i%4, OFFSET_TOP +4 -i/4, c);
    }
  }
  if (current_test == 2) {
    // one digit, 4x6 rectangle
    matrix.draw3x5Digit(hour % 10, 0, 2, color1);
    uint32_t c;
    uint8_t OFFSET_LEFT = 4;
    uint8_t OFFSET_TOP = 1;
    for (uint8_t i=0; i < 24; i++) {
      c = (min > i*2.5) ? color1 : color1_dark;
      matrix.drawPixel(OFFSET_LEFT + i%4, OFFSET_TOP +5 -i/4, c);
    }
  }
  if (current_test == 3) {
    // one digit, hand in a 4x4 rectangle
    matrix.draw3x5Digit(hour % 10, 0, 2, color1);
    matrix.fillRect(4, 3, 4, 4, color1_dark);
    matrix.drawBitmap(4, 3, HAND_4x4[(min*12)/60], 4, 4, color1);
  }
  
  if (current_test == 4) {
    // one digit, full-screen hand with 20 bitmaps
    matrix.drawBitmap(0, 0, HAND_20_8x8[min/3], 8, 8, color1);
    uint8_t hand_x = 0;
    if (min > 30)
      hand_x = 5;
    matrix.draw3x5Digit(hour % 10, hand_x, 2, color2);
  }
  if (current_test == 5) {
    // one digit, full-screen hand with 8 bitmaps
    matrix.drawBitmap(0, 0, HAND_8_8x8[min*8/60], 8, 8, color1);
    uint8_t hand_x = 0;
    if (min > 30)
      hand_x = 5;
    matrix.draw3x5Digit(hour % 10, hand_x, 2, color2);
  }
  
  matrix.show();
  return NULL;
}

Mode* MDisplayTest::press() {
  current_test = (current_test + 1) % 6;
  return NULL;
}
Mode* MDisplayTest::longpress() {
  return &m_menu;
}
Mode* MDisplayTest::left_turn() {
  min--;
  if (min < 0) {
    min+=60;
    hour--;
  }
  if (hour < 0) {
    hour += 24;
  }
  return NULL;
}
Mode* MDisplayTest::right_turn() {
  min++;
  if (min >=60) {
    min-=60;
    hour++;
  }
  if (hour >= 24) {
    hour -= 24;
  }
  return NULL;
}