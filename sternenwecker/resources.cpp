#include "resources.h"

ModeMaster mode_master = ModeMaster(&m_test);
AlarmMatrix matrix = AlarmMatrix(LED_PIN, 8, 8);

void setup_resources() {
  Serial.begin(9600);
  // LEDs
  matrix.begin();
  matrix.setBrightness(BRIGHTNESS);
  matrix.fillScreen(matrix.Color(0,0,0));
  matrix.show();
}

void loop_resources() {
  mode_master.loop();
}