#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>
#include "alarm_clock.h"

RTC_DS1307 RTC;

AlarmClock::AlarmClock(alarm_callback_t alarm_callback) : current_hour(0), current_minute(0), last_sync(0), alarm_minute(0), alarm_hour(0), alarm_enabled(false), alarm_callback(alarm_callback), last_alarm_millis(0) {
}

void AlarmClock::setup() {
  Wire.begin();
  RTC.begin();
  // following line sets the RTC to the date & time this sketch was compiled
  // RTC.adjust(DateTime(__DATE__, __TIME__));
}

void AlarmClock::loop() {
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

uint8_t AlarmClock::is_blinker_on() {
  return (millis() / 500) % 2;
}

void AlarmClock::set_time(uint8_t hour, uint8_t minute) {
  RTC.adjust(DateTime(2015, 01, 24, hour, minute, 0)); // we do not care about the date...
}

void AlarmClock::check_alarm() {
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
