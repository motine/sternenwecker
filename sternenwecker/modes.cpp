#include <Arduino.h>
#include "resources.h"
#include "clock.h"
#include "modes.h"

Mode::Mode() {
}

// --------- MOff ----------
MOff m_off = MOff();
void MOff::enter() {
  matrix.clear();
  matrix.show();
}

Mode* MOff::press() {
  return &m_time;
}

// --------- MShowTime ----------
MTime m_time = MTime();

Mode* MTime::loop() {
  uint8_t hour = get_current_hour();
  uint8_t minute = get_current_minute();

  int8_t scroll_offset = 8 - (millis() - enter_millis) / TIME_SCROLL_STEP_DURATION;
  
  if (hour < 10)
    scroll_offset-=4;
  
  if (scroll_offset < -18)
    return &m_off;

  matrix.clear();
  if (hour >= 10)
    matrix.draw3x5Digit(hour / 10, scroll_offset, 2, TIME_COLOR);
  matrix.draw3x5Digit(hour % 10, scroll_offset+4, 2, TIME_COLOR);
  matrix.drawPixel(scroll_offset+8, 3, TIME_COLOR);
  matrix.drawPixel(scroll_offset+8, 5, TIME_COLOR);
  matrix.draw3x5Digit(minute / 10, scroll_offset+11, 2, TIME_COLOR);
  matrix.draw3x5Digit(minute % 10, scroll_offset+15, 2, TIME_COLOR);

  matrix.show();
  return NULL;
}
void MTime::enter() {
  enter_millis = millis();
}
void MTime::leave() {
}

Mode* MTime::press() {
  return &m_menu;
}
Mode* MTime::longpress() {
  return &m_off;
}

// --------- MMenu ----------
MMenu m_menu = MMenu();

static const uint8_t PROGMEM 
  MENU_ICONS[MENU_COUNT][8] = {
    // { B01111111,
    //   B01111111,
    //   B00001111,
    //   B00011111,
    //   B00111011,
    //   B01110011,
    //   B11100011,
    //   B11000000 },
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
      B00100000,
      B00010100,
      B00001100,
      B00011100,
      B00000000,
      B00000000 },
    { B00000000,
      B00000000,
      B00000000,
      B00111100,
      B00000000,
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

void MMenu::update() {
  matrix.drawBitmap(0, 0, MENU_ICONS[current], 8, 8, MENU_COLOR);
  matrix.show();
}

void MMenu::enter() {
  current = 0;
  update();
}

Mode* MMenu::press() {
  switch (current) {
    case 0: return &m_set_alarm;
    case 1: return &m_menu;
    case 2: return &m_torch;
    case 3: return &m_set_time;
    default: return &m_off;
  }
  // TODO
  return &m_menu;
}

Mode* MMenu::longpress() { return &m_off; }

Mode* MMenu::left_turn() {
  current = (current + MENU_COUNT - 1) % MENU_COUNT;
  update();
  return NULL;
}
Mode* MMenu::right_turn() {
  current = (current + 1) % MENU_COUNT;
  update();
  return NULL;
}

// --------- MTorch ----------
MTorch m_torch = MTorch();
void MTorch::update() {
  uint32_t color = matrix.hue_to_color((hue * 360.0)/TORCH_HUE_STEPS);
  matrix.setBrightness(BRIGHTNESS / (float)TORCH_BRIGHTNESS_STEPS * brightness);
  matrix.fillScreen(color);
  matrix.show();
}

void MTorch::enter() {
  hue = TORCH_HUE_START;
  brightness = TORCH_BRIGHTNESS_START;
  update();
}
void MTorch::leave() {
  // clean up and set to default brightness
  matrix.setBrightness(BRIGHTNESS);
}

Mode* MTorch::press() { return &m_off; }
Mode* MTorch::longpress() { return NULL; }
Mode* MTorch::button_hold() {
  hue = (hue + 1) % TORCH_HUE_STEPS;
  update();
  return NULL;
}

Mode* MTorch::left_turn() {
  if (brightness > TORCH_BRIGHTNESS_MIN) {
    brightness--;
  }
  update();
  return NULL;
}
Mode* MTorch::right_turn() {
  if (brightness < TORCH_BRIGHTNESS_STEPS) {
    brightness++;
  }
  update();
  return NULL;
}

// --------- MSetTime ----------
#define SET_STATE_MINUTE 1
#define SET_STATE_HOUR 2

MSetTime m_set_time = MSetTime();
void MSetTime::update() {
  matrix.clear();
  uint8_t num_to_show = (state == SET_STATE_MINUTE) ? get_current_minute() : get_current_hour();
  uint8_t num_x = (state == SET_STATE_MINUTE) ? 2 : 0;
  uint8_t dots_x = (state == SET_STATE_MINUTE) ? 0 : 7;
  matrix.draw3x5Digit(num_to_show / 10, num_x, 2, SET_TIME_COLOR);
  matrix.draw3x5Digit(num_to_show % 10, num_x+3, 2, SET_TIME_COLOR);
  if (get_current_second() % 2 == 0) {
    matrix.drawPixel(dots_x, 3, SET_TIME_COLOR);
    matrix.drawPixel(dots_x, 5, SET_TIME_COLOR);
  }
  matrix.show();
}

void MSetTime::enter() {
  state = SET_STATE_HOUR;
  update();
}

Mode* MSetTime::loop() {
  update();
  return NULL;
}

Mode* MSetTime::press() {
  switch (state) {
  case SET_STATE_HOUR:
    state = SET_STATE_MINUTE;
    update();
    return NULL;
  case SET_STATE_MINUTE:
    return &m_off;
  }
  return NULL;
}
Mode* MSetTime::longpress() { return &m_menu; }
Mode* MSetTime::left_turn() {
  if (state == SET_STATE_HOUR)
    subtract_hour_from_offset();
  if (state == SET_STATE_MINUTE)
    subtract_minute_from_offset();

  update();
  return NULL;
}
Mode* MSetTime::right_turn() {
  if (state == SET_STATE_HOUR)
    add_hour_to_offset();
  if (state == SET_STATE_MINUTE)
    add_minute_to_offset();

  update();
  return NULL;
}

// --------- MSetAlarm ----------
MSetAlarm m_set_alarm = MSetAlarm();

static const uint8_t PROGMEM 
  ALARM_OFF[8] = {
      B00000000,
      B00000000,
      B01000010,
      B00100100,
      B00011000,
      B00100100,
      B01000010,
      B00000000 };

void MSetAlarm::update() {
  matrix.clear();
  if (get_alarm_enabled()) {
    matrix.draw3x5Digit(get_alarm_hour(), 0, 2, SET_ALARM_COLOR_HOUR);
    uint8_t min = get_alarm_minute();
    matrix.draw3x5Digit(min / 10, 3, 2, SET_ALARM_COLOR_MINUTE);
    matrix.draw3x5Digit(min % 10, 6, 2, SET_ALARM_COLOR_MINUTE);
  } else {
    matrix.drawBitmap(0, 0, ALARM_OFF, 8, 8, SET_ALARM_COLOR_OFF);
  }
  matrix.show();
}

void MSetAlarm::enter() {
  update();
}

Mode* MSetAlarm::press() {
  return &m_off;
}
Mode* MSetAlarm::longpress() { return &m_menu; }

void MSetAlarm::change_alarm(int8_t add) {
  int8_t new_min = get_alarm_minute() + add;
  int8_t new_hour = get_alarm_hour();
  bool new_enabled = true;
  
  if (!get_alarm_enabled() && (add > 0)) { // exception: oho, we just enabled the alarm
    new_hour = MIN_ALARM_HOUR;
    new_min = 0;
    new_enabled = true;
  }
  
  if (new_min < 0) {
    new_min+= 60;
    new_hour-= 1;
  }
  if (new_min >= 60) {
    new_min-= 60;
    new_hour+= 1;
  }
  if (new_hour < MIN_ALARM_HOUR) {
    new_hour = MIN_ALARM_HOUR;
    new_min = 0;
    new_enabled = false;
  }
  if (new_hour > MAX_ALARM_HOUR) {
    new_hour = MAX_ALARM_HOUR;
    new_min = 45;
  }
  set_alarm_hour(new_hour);
  set_alarm_minute(new_min);
  set_alarm_enabled(new_enabled);
  update();
}

Mode* MSetAlarm::left_turn() {
  if (!get_alarm_enabled()) // ignore left turns if the alarm is off anyway
    return NULL;
  change_alarm(-15);
  return NULL;
}
Mode* MSetAlarm::right_turn() {
  change_alarm(+15);
  return NULL;
}