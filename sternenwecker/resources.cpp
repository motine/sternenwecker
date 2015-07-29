#include "resources.h"

ModeMaster mode_master = ModeMaster(&m_time);

void button_press(uint8_t button_pin) {
  mode_master.press();
}
void button_longpress(uint8_t button_pin) {
  mode_master.longpress();
}
void button_hold(uint8_t button_pin) {
  mode_master.button_hold();
}

void encoder_left_turn() {
  mode_master.left_turn();
}
void encoder_right_turn() {
  mode_master.right_turn();
}

void alarm_fired() {
  mode_master.setModeUnlessNull(&m_alarming);
}

AlarmMatrix matrix = AlarmMatrix();
AlarmStrip strip = AlarmStrip(STRIP_WIDTH, STRIP_PIN);
Button button = Button(ENCODER_BUTTON_PIN, button_press, button_longpress, button_hold);
Encoder encoder = Encoder(ENCODER_A_PIN, ENCODER_B_PIN, encoder_left_turn, encoder_right_turn);
AlarmClock clock = AlarmClock(alarm_fired);

void setup_resources() {
  // LEDs
  matrix.begin(0x70);
  matrix.setRotation(3);

  strip.setup();
  strip.setBrightness(STRIP_BRIGHTNESS);

  button.setup();
  encoder.setup();
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  clock.setup();
  
  mode_master.setup();
}

void loop_resources() {
  clock.loop();
  button.loop();
  encoder.loop();
  mode_master.loop();
}