#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>
#include "clock.h"

RTC_DS1307 RTC;

void check_alarm();

uint8_t current_hour = 0;
uint8_t current_minute = 0;
unsigned long last_sync = 0;

void setup_clock() {
  Wire.begin();
  RTC.begin();
  // following line sets the RTC to the date & time this sketch was compiled
  // RTC.adjust(DateTime(__DATE__, __TIME__));
}

void loop_clock() {
  // sync current time variables
  if (millis() - last_sync > TIME_SYNC_INTERVAL) {
    last_sync = millis();
    DateTime now = RTC.now();
    current_hour = now.hour();
    current_minute = now.minute();
    // check for alarm
    check_alarm();
  }
}

uint8_t is_blinker_on() {
  return (millis() / 500) % 2;
}

uint8_t alarm_minute = 0;
uint8_t alarm_hour = 0;
bool alarm_enabled = false;
alarm_callback_t alarm_callback;
unsigned long last_alarm_millis = 0;

void check_alarm() {
  if (!alarm_enabled) { // alarm is off
    return;
  }
  if (last_alarm_millis + 61000 > millis()) { // the alarm was just fired, so we don't want to fire again
      // TODO deal with millis() overflow
      return;
  }
  if ((current_hour == alarm_hour) && (current_minute == alarm_minute)) {
    alarm_callback();
    last_alarm_millis = millis();
  }
}

// setting the alarm time
void set_alarm_hour(uint8_t hour) {
  alarm_hour = hour;
}
void set_alarm_minute(uint8_t minute) {
  alarm_minute = minute;
}
void set_alarm_enabled(bool enabled) {
  alarm_enabled = enabled;    
}
