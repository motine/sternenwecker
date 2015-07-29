#ifndef RESOURCES_H
#define RESOURCES_H

#include "alarm_matrix.h"
#include "alarm_strip.h"
#include "mode_master.h"
#include "button.h"
#include "encoder.h"
#include "alarm_clock.h"

#define STRIP_PIN 6
#define STRIP_WIDTH 60
#define STRIP_BRIGHTNESS 255 // Do not run the program with a brightness above 20 when powering the LED matrix via Arduino's power PINs.
#define ENCODER_A_PIN 3
#define ENCODER_B_PIN 2
#define ENCODER_BUTTON_PIN 4


extern ModeMaster mode_master;
extern AlarmMatrix matrix;
extern AlarmStrip strip;
extern Button button;
extern Encoder encoder;
extern AlarmClock clock;

void setup_resources();
void loop_resources();

#endif
