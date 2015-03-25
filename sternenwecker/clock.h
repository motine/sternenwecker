#ifndef CLOCK_H
#define CLOCK_H

// getting the time
uint8_t get_current_hour();
uint8_t get_current_minute();
uint8_t get_current_second();
uint8_t get_current_halfsecond();

// setting the current time
void add_hour_to_offset();
void add_minute_to_offset();
void subtract_hour_from_offset();
void subtract_minute_from_offset();

// getting the alarm time
uint8_t get_alarm_hour();
uint8_t get_alarm_minute();
uint8_t get_alarm_enabled();
bool alarm_is_due();
void alarm_fired(); // notify this module, that the alarm was fired (so alarm_is_due only returns true if there has not just been an alarm set off)

// setting the alarm time
void set_alarm_hour(uint8_t hour);
void set_alarm_minute(uint8_t minute);
void set_alarm_enabled(bool enabled);

#endif CLOCK_H