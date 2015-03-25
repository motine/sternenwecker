#ifndef RESOURCES_H
#define RESOURCES_H

#include "alarm_matrix.h"
#include "mode_master.h"
#include "button.h"
#include "encoder.h"
#include "clock.h"

#define ENCODER_A_PIN 3
#define ENCODER_B_PIN 2
#define ENCODER_BUTTON_PIN 4

#define LED_PIN 6
#define BRIGHTNESS 255 // Do not run the program with a brightness above 20 when powering the LED matrix via Arduino's power PINs.

extern ModeMaster mode_master;
extern AlarmMatrix matrix;
extern Button button;
extern Encoder encoder;

void setup_resources();
void loop_resources();

#endif
