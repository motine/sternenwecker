#include <Arduino.h>
#include "encoder.h"


Encoder::Encoder(uint8_t pin_a, uint8_t pin_b, encoder_callback_t left_turn, encoder_callback_t right_turn) :
  pin_a(pin_a), pin_b(pin_b), callback_left_turn(left_turn), callback_right_turn(right_turn), last_b(0) {
}

void Encoder::setup() {
  pinMode(pin_a, INPUT_PULLUP);
  pinMode(pin_b, INPUT_PULLUP);
}

void Encoder::loop() {
  int a = digitalRead(pin_a);
  int b = digitalRead(pin_b);
  if ((last_b != b) && (a == LOW)) { // only if we have an edge change in B
    if (b == HIGH) {
      if (callback_right_turn != NULL)
        callback_right_turn();
    } else {
      if (callback_left_turn != NULL)
        callback_left_turn();
    }
  }
  last_b = b;
}