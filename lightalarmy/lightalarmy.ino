#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 6

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, LED_PIN, NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE, NEO_GRB + NEO_KHZ800);

const uint16_t RED    = matrix.Color(255, 0, 0);
const uint16_t YELLOW = matrix.Color(255, 255, 0);
const uint16_t GREEN  = matrix.Color(0, 255, 0);

// static const uint8_t PROGMEM
//   ANIMATION[ANIMATION_LENGTH][LINE_COUNT] =
//   {
//     { B10000000,
//       B01000000,
//       B00100000,
//       B00010000,
//       B00001000,
//       B00000100,
//       B00000010,
//       B00000001,
//       B00000110 },
//     { B10000000,
//       B00100000,
//       B00010000,
//       B00001000,
//       B00000100,
//       B00000010,
//       B00000001,
//       B01000000,
//       B00000110 },
//     { B01000000,
//       B10000000,
//       B00010000,
//       B00100000,
//       B00001000,
//       B00000010,
//       B00000100,
//       B00000001,
//       B00000110 }
//   };
//
void setup() {
  // Serial
  Serial.begin(9600);
  
  // LEDs
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(255);
  matrix.setTextColor(RED);
  matrix.fillScreen(0);
  matrix.setCursor(0, 0);
  
}

void loop() {
  uint16_t color = matrix.Color(200, 200, 255);
  for(uint8_t i = 0; i < 8; i++) {
    matrix.drawLine(0, i, 7, i, color);
  }
  // matrix.drawBitmap(0, 0, ANIMATION[current_frame], 8, 8, RED);
  matrix.show();
  
  delay(200);
}