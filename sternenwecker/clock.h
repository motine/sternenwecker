#ifndef CLOCK_H
#define CLOCK_H

uint8_t get_current_hour();
uint8_t get_current_minute();
uint8_t get_current_second();

void add_hour_to_offset();
void add_minute_to_offset();
void substract_hour_from_offset();
void substract_minute_from_offset();

#endif CLOCK_H