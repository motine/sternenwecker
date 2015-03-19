#include <Arduino.h>
#include "resources.h"
#include "modes.h"

Mode::Mode() {
}

// --------- MOff ----------
MOff m_off = MOff();
void MOff::enter() {
  matrix.clear();
  matrix.show();
}

Mode* MOff::press() {
  return &m_menu;
}

// --------- MMenu ----------
MMenu m_menu = MMenu();

static const uint8_t PROGMEM 
  MENU_ICONS[MENU_COUNT][8] = {
    // { B01111111,
    //   B01111111,
    //   B00001111,
    //   B00011111,
    //   B00111011,
    //   B01110011,
    //   B11100011,
    //   B11000000 },
    { B00000000,
      B00000000,
      B00011100,
      B00001100,
      B00010100,
      B00100000,
      B00000000,
      B00000000 },
    { B00000000,
      B00000000,
      B00100000,
      B00010100,
      B00001100,
      B00011100,
      B00000000,
      B00000000 },
    { B00000000,
      B00000000,
      B00000000,
      B00111100,
      B00000000,
      B00111100,
      B00000000,
      B00000000 },
    { B00000000,
      B00000000,
      B00011000,
      B00011000,
      B00000000,
      B00011000,
      B00000000,
      B00000000 },
    };

void MMenu::update() {
  matrix.drawBitmap(0, 0, MENU_ICONS[current], 8, 8, MENU_COLOR);
  matrix.show();
}

void MMenu::enter() {
  current = 0;
  update();
}

Mode* MMenu::press() {
  switch (current) {
    case 0: return &m_menu;
    case 1: return &m_menu;
    case 2: return &m_torch;
    case 3: return &m_menu;
    default: return &m_off;
  }
  // TODO
  return &m_menu;
}

Mode* MMenu::longpress() { return &m_off; }

Mode* MMenu::left_turn() {
  current = (current + MENU_COUNT - 1) % MENU_COUNT;
  update();
  return NULL;
}
Mode* MMenu::right_turn() {
  current = (current + 1) % MENU_COUNT;
  update();
  return NULL;
}

// --------- MTorch ----------
MTorch m_torch = MTorch();
void MTorch::update() {
  uint32_t color = matrix.hue_to_color((hue * 360.0)/TORCH_HUE_STEPS);
  matrix.setBrightness(BRIGHTNESS / (float)TORCH_BRIGHTNESS_STEPS * brightness);
  matrix.fillScreen(color);
  matrix.show();
}

void MTorch::enter() {
  hue = TORCH_HUE_START;
  brightness = TORCH_BRIGHTNESS_START;
  update();
}
void MTorch::leave() {
  // clean up and set to default brightness
  matrix.setBrightness(BRIGHTNESS);
}

Mode* MTorch::press() { return &m_off; }
Mode* MTorch::longpress() { return NULL; }
Mode* MTorch::button_hold() {
  hue = (hue + 1) % TORCH_HUE_STEPS;
  update();
  return NULL;
}

Mode* MTorch::left_turn() {
  if (brightness > 0) {
    brightness--;
  }
  update();
  return NULL;
}
Mode* MTorch::right_turn() {
  if (brightness < TORCH_BRIGHTNESS_STEPS) {
    brightness++;
  }
  update();
  return NULL;
}