#ifndef ALARM_CLOCK_H
#define ALARM_CLOCK_H

// getting the time
#define TIME_SYNC_INTERVAL 1000 // ms

// getting the alarm time
typedef void (*alarm_callback_t)();

class AlarmClock {
  public:
    AlarmClock(alarm_callback_t alarm_callback);
    void setup();
    void loop();

    uint8_t current_hour;   // read-only
    uint8_t current_minute; // read-only
    uint8_t is_blinker_on(); // returns boolean if the dots between hour and minute shall be on

    uint8_t alarm_minute;
    uint8_t alarm_hour;
    bool alarm_enabled;
    alarm_callback_t alarm_callback; // callback to be called when the alarm goes off
  protected:
    unsigned long last_sync;
    unsigned long last_alarm_millis;
    void check_alarm();
};
#endif