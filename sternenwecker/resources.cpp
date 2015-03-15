#include "resources.h"

ModeMaster mode_master = ModeMaster(&m_test);

void button_press(uint8_t button_pin) {
  mode_master.press();
}
void button_longpress(uint8_t button_pin) {
  mode_master.longpress();
}

void encoder_left_turn() {
  mode_master.left_turn();
}
void encoder_right_turn() {
  mode_master.right_turn();
}

AlarmMatrix matrix = AlarmMatrix(LED_PIN, 8, 8);
Button button = Button(ENCODER_BUTTON_PIN, button_press, button_longpress);
Encoder encoder = Encoder(ENCODER_A_PIN, ENCODER_B_PIN, encoder_left_turn, encoder_right_turn);

void setup_resources() {
  // LEDs
  matrix.begin();
  matrix.setBrightness(BRIGHTNESS);
  matrix.clear();
  matrix.show();

  button.setup();
  encoder.setup();

  mode_master.setup();
}

void loop_resources() {
  button.loop();
  encoder.loop();
  mode_master.loop();
}