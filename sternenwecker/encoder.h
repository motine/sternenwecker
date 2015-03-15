#ifndef ENCODER_H
#define ENCODER_H

typedef void (*encoder_callback_t)(void);

class Encoder {
  public:
    Encoder(uint8_t pin_a, uint8_t pin_b, encoder_callback_t left_trun, encoder_callback_t right_turn);
    void setup();
    void loop();

  protected:
    const encoder_callback_t callback_left_turn;
    const encoder_callback_t callback_right_turn;
    const uint8_t pin_a;
    const uint8_t pin_b;
    int last_b;
};

#endif
