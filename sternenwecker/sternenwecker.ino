#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "alarm_matrix.h"

#define ENCODER_A_PIN 3
#define ENCODER_B_PIN 2
#define ENCODER_BUTTON_PIN 4

#define LED_PIN 6
#define MAX_BRIGHTNESS 20 // Do not run the program with a brightness above 20 when powering the LED matrix via Arduino's power PINs.
AlarmMatrix matrix = AlarmMatrix(LED_PIN);

const uint16_t BLACK  = matrix.Color(0,0,0);
const uint16_t WHITE  = matrix.Color(255, 255, 255);
const uint16_t RED    = matrix.Color(255, 0, 0);
const uint16_t GREEN  = matrix.Color(0, 255, 0);
const uint16_t BLUE  = matrix.Color(0, 0, 255);
const uint16_t YELLOW = matrix.Color(255, 255, 0);

#define COLOR_COUNT 4
const uint16_t COLORS[COLOR_COUNT] = {WHITE, RED, GREEN, BLUE};
#define BRIGHTNESS_STEPS 3

volatile uint8_t counter_a = 0;
volatile uint8_t counter_b = 5;

void setup() {
  // Serial
  Serial.begin(9600);
  
  pinMode(ENCODER_A_PIN, INPUT_PULLUP);
  pinMode(ENCODER_B_PIN, INPUT_PULLUP);
  pinMode(ENCODER_BUTTON_PIN, INPUT_PULLUP);
  
  // attachInterrupt(0, encoder_a_isr, CHANGE);
  // attachInterrupt(1, encoder_b_isr, CHANGE);
  
  // LEDs
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(MAX_BRIGHTNESS);
  // matrix.setTextColor(RED);
  matrix.fillScreen(BLACK);
  // matrix.setCursor(0, 0);
}
int last_b = 0;

void loop() {
  if (digitalRead(ENCODER_BUTTON_PIN) == LOW) {
    counter_a++;
  }
  
  int a = digitalRead(ENCODER_A_PIN);
  int b = digitalRead(ENCODER_B_PIN);
  if ((last_b != b) && (a == LOW)) { // only if we have an edge change in B
    if (b == HIGH) {
      counter_b++;
    } else {
      counter_b--;
    }
  }
  last_b = b;
  
  // if ((a == HIGH) && (b == LOW)) {
  //   counter_b--;
  // }


  matrix.fillScreen(BLACK);
  matrix.draw3x5Digit(counter_a % 10, 1, 1, RED);
  matrix.draw3x5Digit(counter_b % 10, 4, 1, BLUE);
  matrix.show();
  
  // // uint16_t color = matrix.Color(0, 0, 50);
  // // for(uint8_t i = 0; i < 8; i++) {
  // //   matrix.drawLine(0, i, 7, i, color);
  // // }
  // // matrix.drawBitmap(0, 0, ANIMATION[current_frame], 8, 8, RED);
  // for (int color_index=0; color_index < COLOR_COUNT; color_index++) {
  //   for (int brightness=1; brightness <= BRIGHTNESS_STEPS; brightness++) {
  //     matrix.setBrightness((int)(MAX_BRIGHTNESS/(float)BRIGHTNESS_STEPS * brightness));
  //     // show filled screen
  //     matrix.fillScreen(COLORS[color_index]);
  //     matrix.show();
  //     delay(1500);
  //     // show count up
  //     for (int counter=0; counter < 20; counter++) {
  //       matrix.fillScreen(BLACK);
  //       matrix.draw3x5Digit(counter / 10, 1, 1, COLORS[color_index]);
  //       matrix.draw3x5Digit(counter % 10, 4, 1, COLORS[color_index]);
  //       matrix.show();
  //       delay(200);
  //     }
  //   }
  // }
  
}