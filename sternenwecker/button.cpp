#include <Arduino.h>
#include "button.h"

Button::Button(uint8_t pin, callback_t button_press, callback_t button_longpress, callback_t button_down, callback_t button_up) :
  pin(pin), press_callback_triggered(false), millis_down(0), callback_button_down(button_down), callback_button_up(button_up), callback_button_press(button_press), callback_button_longpress(button_longpress) {
}
void Button::setup() {
  pinMode(pin, INPUT_PULLUP);
}

void Button::loop() {
  int pin_state = digitalRead(pin);
  if (millis_down == 0) { // the button was up before
    if (pin_state == LOW) { // we have a push down
      millis_down = millis();
      if (callback_button_down != NULL)
        callback_button_down(pin);
      press_callback_triggered = false;
    }
  } else { // button was down before
    if (pin_state == HIGH) { // we have a release
      if (callback_button_up != NULL)
        callback_button_up(pin);
      if (!press_callback_triggered) {
        if (callback_button_press != NULL)
          callback_button_press(pin);
        press_callback_triggered = true;
      }
      millis_down = 0;
    } else { // we are still pressing
      if (millis() >= (millis_down+BUTTON_LONGPRESS_DURATION)) { // we have a long press
        if (callback_button_longpress != NULL)
          callback_button_longpress(pin);
        press_callback_triggered = true;
      }
    }
  }
}