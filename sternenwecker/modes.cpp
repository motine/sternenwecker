#include <Arduino.h>
#include "resources.h"
#include "clock.h"
#include "display_test.h"
#include "modes.h"

Mode::Mode() {
}

// --------- MOff ----------
MOff m_off = MOff();
void MOff::enter() {
  matrix.clear();
  matrix.show();
}

Mode* MOff::loop() {
  delay(50); // reduce the load during off
  return NULL;
}

Mode* MOff::press() {
  return &m_time;
}
Mode* MOff::longpress() {
  return &m_display_test; // hidden easter egg (testing)
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

void MMenu::update() {
  matrix.displayMenuIcon((menu_icon_t)current, MENU_COLOR);
}

void MMenu::enter() {
  current = 0;
  update();
}

Mode* MMenu::press() {
  switch (current) {
    case 0: return &m_sunset;
    case 1: return &m_set_alarm;
    case 2: return &m_torch;
    case 3: return &m_set_time;
  }
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
  uint8_t number = (state == SET_STATE_MINUTE) ? get_current_minute() : get_current_hour();
  bool dots_left = (state == SET_STATE_MINUTE);
  bool show_dots = (get_current_halfsecond() % 2 == 0);
  matrix.displayTimeComponent(number, dots_left, show_dots, SET_TIME_COLOR);
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
    return &m_confirm;
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

void MSetAlarm::update() {
  if (get_alarm_enabled())
    matrix.displayDigitAndHand(get_alarm_hour(), get_alarm_minute(), SET_ALARM_DIGIT_COLOR, SET_ALARM_HAND_COLOR, SET_ALARM_OVERLAP_COLOR);
  else
    matrix.displayOff(SET_ALARM_COLOR_OFF);
}

void MSetAlarm::enter() {
  update();
}

Mode* MSetAlarm::press() {
  return &m_confirm;
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

// --------- MAlarming ----------
MAlarming m_alarming = MAlarming();
void MAlarming::enter() {
  start_millis = millis();
  start_show_time_millis = 0;
}

Mode* MAlarming::loop() {
  if (start_show_time_millis + ALARMING_SHOW_TIME_DURATION > millis()) {
    matrix.clear();
    matrix.displayDigitAndHand(get_current_hour(), get_current_minute(), ALARMING_DIGIT_COLOR, ALARMING_HAND_COLOR, ALARMING_OVERLAP_COLOR);
    matrix.show();
    return NULL;
  }
  
  double pos;
  unsigned long millis_since_start = millis() - start_millis;
  if (millis_since_start > ALARMING_AUTO_OFF)
    return &m_off;
  if (millis_since_start > ALARMING_RISE_DURATION)
    pos = 1.0;
  else
    pos = fmod((double)millis_since_start / ALARMING_RISE_DURATION, 1.0);
  
  uint8_t r = pow(pos, 2) * 255;
  uint8_t g = pow(pos, 3) * 255;
  uint8_t b = pow(pos, 5) * 150;
  matrix.fillScreen(matrix.Color(r,g,b));
  matrix.show();
  return NULL;
}

Mode* MAlarming::press() {
  start_show_time_millis = millis();
  return NULL;
}
Mode* MAlarming::longpress() {
  return &m_off;
}

// --------- MSunset ----------
MSunset m_sunset = MSunset();
void MSunset::enter() {
  start_millis = millis();
}

Mode* MSunset::loop() {
  unsigned long millis_since_start = millis() - start_millis;
  if (millis_since_start >= SUNSET_DURATION)
    return &m_off;

  double pos = (double)millis_since_start / SUNSET_DURATION;
  uint8_t r = (1.0-pos) * 60;
  uint8_t g = (1.0-pos) * 30;
  matrix.fillScreen(matrix.Color(r,g,0));
  matrix.show();
  return NULL;
}

Mode* MSunset::press() {
  return &m_off;
}
Mode* MSunset::longpress() {
  return &m_menu;
}
Mode* MSunset::left_turn() {
  start_millis -= SUNSET_TURN_VALUE; // TODO this can lead to an error if millis is still a low number
  return NULL;
}
Mode* MSunset::right_turn() {
  start_millis += SUNSET_TURN_VALUE;
  if (start_millis > millis())
    start_millis = millis();
  return NULL;
}

// --------- MConfirm ----------
MConfirm m_confirm = MConfirm();
void MConfirm::enter() {
  enter_millis = millis();
  matrix.displayConfirm(CONFIRM_COLOR);
}

Mode* MConfirm::loop() {
  if (enter_millis + CONFIRM_DURATION > millis())
    return NULL;
  else
    return &m_off;
}

Mode* MConfirm::press() {
  return &m_off;
}
