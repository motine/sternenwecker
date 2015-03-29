#include <Arduino.h>
#include "clock.h"

uint8_t minute_offset = 0;
uint8_t hour_offset = 0;

#define MINUTE_VALUE 60000UL
#define HOUR_VALUE 3600000UL
#define SECOND_VALUE 1000
#define HALF_SECOND_VALUE 500

unsigned long shifted_millis() {
  return millis() + minute_offset * MINUTE_VALUE + hour_offset * HOUR_VALUE;
}
uint8_t get_current_hour() {
  return (shifted_millis() / HOUR_VALUE) % 24;
}
uint8_t get_current_minute() {
  return (shifted_millis() / MINUTE_VALUE) % 60;
}
uint8_t get_current_second() {
  return (shifted_millis() / SECOND_VALUE) % 60;
}
uint8_t get_current_halfsecond() {
  return (shifted_millis() / HALF_SECOND_VALUE) % 120;
}

void add_hour_to_offset() {
  hour_offset = (hour_offset + 1) % 24;
}
void add_minute_to_offset() {
  minute_offset = (minute_offset + 1) % 60;
}
void subtract_hour_from_offset() {
  hour_offset = (hour_offset + 24 - 1) % 24;
}
void subtract_minute_from_offset() {
  minute_offset = (minute_offset + 60 - 1) % 60;
}

uint8_t alarm_minute = 0;
uint8_t alarm_hour = 0;
bool alarm_enabled = false;
unsigned long last_alarm_millis = 0;

uint8_t get_alarm_hour() {
  return alarm_hour;
}
uint8_t get_alarm_minute() {
  return alarm_minute;
}
uint8_t get_alarm_enabled() {
  return alarm_enabled;
}

bool alarm_is_due() {
  if (!alarm_enabled) { // alarm is off
    return false;
  }
  if (last_alarm_millis + 61000 > millis()) { // the alarm was just fired, so we don't want to fire again
      // TODO deal with millis() overflow
      return false;
  }
  return (get_current_hour() == alarm_hour) && (get_current_minute() == alarm_minute);
}

void alarm_fired() {
  last_alarm_millis = millis();
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
