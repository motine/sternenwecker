#include "resources.h"

ModeMaster mode_master = ModeMaster(&m_test);

void button_press(uint8_t button_pin) {
  mode_master.press();
}
void button_longpress(uint8_t button_pin) {
  mode_master.longpress();
}

AlarmMatrix matrix = AlarmMatrix(LED_PIN, 8, 8);
Button button = Button(ENCODER_BUTTON_PIN, button_press, button_longpress);

void setup_resources() {
  // LEDs
  matrix.begin();
  matrix.setBrightness(BRIGHTNESS);
  matrix.clear();
  matrix.show();

  button.setup();

  mode_master.setup();
}

void loop_resources() {
  button.loop();
  mode_master.loop();
}