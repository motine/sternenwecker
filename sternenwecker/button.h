#ifndef BUTTON_H
#define BUTTON_H

#define BUTTON_LONGPRESS_DURATION 500 // ms

typedef void (*button_callback_t)(uint8_t button_pin);

class Button {
  public:
    Button(uint8_t pin, button_callback_t button_press, button_callback_t button_longpress=NULL, button_callback_t button_down=NULL, button_callback_t button_up=NULL);
    void setup();
    void loop();

  protected:
    unsigned long millis_down; // when did it go down? 0 if the button is up
    bool press_callback_triggered; // if a down action was deteced, we need to keep track if we already called the callback
    const button_callback_t callback_button_down;
    const button_callback_t callback_button_up;
    const button_callback_t callback_button_press;
    const button_callback_t callback_button_longpress;
    const uint8_t pin;
};

#endif /* end of include guard: BUTTON_H */
