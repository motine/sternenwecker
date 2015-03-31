#ifndef CLOCK_H
#define CLOCK_H

// getting the time
#define TIME_SYNC_INTERVAL 1000 // ms

extern uint8_t current_hour;
extern uint8_t current_minute;

void setup_clock();
void loop_clock();
// returns boolean if the dots between hour and minute shall be on
uint8_t is_blinker_on();

// getting the alarm time
typedef void (*alarm_callback_t)();

extern uint8_t alarm_minute;
extern uint8_t alarm_hour;
extern bool alarm_enabled;
extern alarm_callback_t alarm_callback; // callback to be called when the alarm goes off

// setting the alarm time
void set_alarm_hour(uint8_t hour);
void set_alarm_minute(uint8_t minute);
void set_alarm_enabled(bool enabled);

#endif