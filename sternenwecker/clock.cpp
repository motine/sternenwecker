#include <Arduino.h>
#include "clock.h"

uint8_t minute_offset = 0;
uint8_t hour_offset = 0;

#define MINUTE_VALUE 60000UL
#define HOUR_VALUE 3600000UL
#define SECOND_VALUE 1000

unsigned long shifted_millis() {
  return millis() + minute_offset * MINUTE_VALUE + hour_offset * HOUR_VALUE;
}
uint8_t get_current_hour() {
  return (shifted_millis() / HOUR_VALUE) % 60;
}
uint8_t get_current_minute() {
  return (shifted_millis() / MINUTE_VALUE) % 60;
}
uint8_t get_current_second() {
  return (shifted_millis() / SECOND_VALUE) % 60;
}

void add_hour_to_offset() {
  hour_offset = (hour_offset + 1) % 24;
}
void add_minute_to_offset() {
  minute_offset = (minute_offset + 1) % 60;
}
void substract_hour_from_offset() {
  hour_offset = (hour_offset + 24 - 1) % 24;
}
void substract_minute_from_offset() {
  minute_offset = (minute_offset + 60 - 1) % 60;
}
