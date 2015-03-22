#include <Arduino.h>
#include "button.h"

Button::Button(uint8_t pin, button_callback_t button_press, button_callback_t button_longpress, button_callback_t button_hold, button_callback_t button_down, button_callback_t button_up) :
  pin(pin), press_callback_triggered(false), millis_down(0), callback_button_down(button_down), callback_button_up(button_up), callback_button_press(button_press), callback_button_hold(button_hold), callback_button_longpress(button_longpress) {
}
void Button::setup() {
  pinMode(pin, INPUT_PULLUP);
}

void Button::loop() {
  int pin_state = digitalRead(pin);
  
  if (millis_last_edge+BUTTON_DEBOUNCE_INTERVAL > millis()) // we are still waiting for the debounce intervall to pass by
    return;

  if (millis_down == 0) { // the button was up before
    if (pin_state == LOW) { // we have a push down
      millis_down = millis();
      if (callback_button_down != NULL)
        callback_button_down(pin);
      press_callback_triggered = false;
      millis_last_hold_fired = millis_down;
      millis_last_edge = millis_down;
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
      millis_last_edge = millis();
      millis_down = 0;
    } else { // we are still pressing
      if (millis() >= (millis_down+BUTTON_LONGPRESS_DURATION)) { // we have a long press
        if (!press_callback_triggered) {
          if (callback_button_longpress != NULL)
            callback_button_longpress(pin);
          press_callback_triggered = true;
        }
      }
      if (millis_last_hold_fired+BUTTON_HOLD_FREQUENCY < millis()) {
        millis_last_hold_fired = millis();
        callback_button_hold(pin);
      }
    }
  }
}