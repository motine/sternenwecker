#include <Arduino.h>
#include "resources.h"
#include "alarm_clock.h"
#include "display_test.h"
#include "modes.h"

TimeShow::TimeShow(uint32_t duration, bool use_dim_colors) : duration(duration), use_dim_colors(use_dim_colors), start_millis(0) {

}

void TimeShow::start() {
  start_millis = millis();
}
bool TimeShow::is_showing() {
  return start_millis + duration > millis();
}

bool TimeShow::show() {
  if (is_showing()) {
    matrix.clear();
    if (use_dim_colors)
      matrix.displayDigitAndHand(clock.current_hour, clock.current_minute, TIME_DIGIT_DIM_COLOR, TIME_HAND_DIM_COLOR, TIME_OVERLAP_DIM_COLOR);
    else
      matrix.displayDigitAndHand(clock.current_hour, clock.current_minute, TIME_DIGIT_COLOR, TIME_HAND_COLOR, TIME_OVERLAP_COLOR);
    matrix.show();
    return true;
  }
  return false;
}

// --------- MOff ----------
MOff m_off = MOff();
void MOff::enter() {
  matrix.clear();
  matrix.show();
}

Mode* MOff::loop() {
  delay(IDLE_DELAY); // reduce the load during off
  return NULL;
}

Mode* MOff::press() {
  return &m_time;
}
Mode* MOff::longpress() {
  // return &m_alarming; // hidden easter egg (testing)
  return &m_display_test; // hidden easter egg (testing)
}

// --------- MTime ----------
MTime m_time = MTime();

Mode* MTime::loop() {
  if (time_show.show())
    return NULL;
  else
    return &m_off;
}
void MTime::enter() {
  time_show.start();
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
  float normalized_brightness = brightness / (float)TORCH_BRIGHTNESS_STEPS;
  uint32_t color = matrix.hsv_to_color((hue * 360.0)/TORCH_HUE_STEPS, 1.0-0.3*pow(normalized_brightness, 3), normalized_brightness);
  matrix.fillScreen(color);
  matrix.show();
}

void MTorch::enter() {
  enter_millis = millis();
  hue = TORCH_HUE_START;
  brightness = 0.5;
}
Mode* MTorch::loop() {
  if ((millis() - enter_millis) > TORCH_AUTO_OFF)
    return &m_off;
  if (time_show.show())
    return NULL;
  update();
  return NULL;
}
Mode* MTorch::press() {
  if (time_show.is_showing()) {
    return &m_off;
  } else {
    time_show.start();
    return NULL;
  }
}
Mode* MTorch::longpress() {
  return NULL;
}
Mode* MTorch::button_hold() {
  hue = (hue + 1) % TORCH_HUE_STEPS;
  return NULL;
}

Mode* MTorch::left_turn() {
  if (brightness > TORCH_BRIGHTNESS_MIN)
    brightness--;
  return NULL;
}
Mode* MTorch::right_turn() {
  if (brightness < TORCH_BRIGHTNESS_STEPS)
    brightness++;
  return NULL;
}

// --------- MSetTime ----------
#define SET_STATE_MINUTE 1
#define SET_STATE_HOUR 2

MSetTime m_set_time = MSetTime();
void MSetTime::update() {
  uint8_t number = (state == SET_STATE_MINUTE) ? minute : hour;
  bool dots_left = (state == SET_STATE_MINUTE);
  bool show_dots = (clock.is_blinker_on() % 2 == 0);
  matrix.displayTimeComponent(number, dots_left, show_dots, SET_TIME_COLOR);
}

void MSetTime::enter() {
  state = SET_STATE_HOUR;
  hour = clock.current_hour;
  minute = clock.current_minute;
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
    clock.set_time(hour, minute);
    return &m_confirm;
  }
  return NULL;
}
Mode* MSetTime::longpress() { return &m_menu; }
Mode* MSetTime::left_turn() {
  if (state == SET_STATE_HOUR)
    hour = (hour + 24 - 1) % 24;
  if (state == SET_STATE_MINUTE)
    minute = (minute + 60 - 1) % 60;

  update();
  return NULL;
}
Mode* MSetTime::right_turn() {
  if (state == SET_STATE_HOUR)
    hour = (hour + 1) % 60;
  if (state == SET_STATE_MINUTE)
    minute = (minute + 1) % 60;

  update();
  return NULL;
}

// --------- MSetAlarm ----------
MSetAlarm m_set_alarm = MSetAlarm();

void MSetAlarm::update() {
  if (clock.alarm_enabled)
    matrix.displayDigitAndHand(clock.alarm_hour, clock.alarm_minute, SET_ALARM_DIGIT_COLOR, SET_ALARM_HAND_COLOR, SET_ALARM_OVERLAP_COLOR);
  else
    matrix.displayOff(SET_ALARM_COLOR_OFF);
}

void MSetAlarm::enter() {
  update();
}

Mode* MSetAlarm::press() {
  return &m_confirm;
}
Mode* MSetAlarm::longpress() { return &m_confirm; }

void MSetAlarm::change_alarm(int8_t add) {
  int8_t new_min = clock.alarm_minute + add;
  int8_t new_hour = clock.alarm_hour;
  bool new_enabled = true;
  
  if (!clock.alarm_enabled && (add > 0)) { // exception: oho, we just enabled the alarm
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
  clock.alarm_hour = new_hour;
  clock.alarm_minute = new_min;
  clock.alarm_enabled =new_enabled;
  update();
}

Mode* MSetAlarm::left_turn() {
  if (!clock.alarm_enabled) // ignore left turns if the alarm is off anyway
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
}

Mode* MAlarming::loop() {
  if (time_show.show())
    return NULL;
    
  double pos;
  unsigned long millis_since_start = millis() - start_millis;
  if (millis_since_start > ALARMING_AUTO_OFF)
    return &m_off;
  if (millis_since_start > ALARMING_RISE_DURATION)
    pos = 1.0;
  else
    pos = fmod((double)millis_since_start / ALARMING_RISE_DURATION, 1.0);
  
  uint8_t r = 1+pow(pos, 2) * 254;
  uint8_t g = pow(pos, 3) * 255;
  uint8_t b = pow(pos, 5) * 150;
  matrix.fillScreen(matrix.Color(r,g,b));
  matrix.show();
  return NULL;
}

Mode* MAlarming::press() {
  time_show.start();
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
  if (time_show.show())
    return NULL;
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
  if (time_show.is_showing()) {
    return &m_off;
  } else {
    time_show.start();
    return NULL;
  }
}
Mode* MSunset::longpress() {
  return &m_off;
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
