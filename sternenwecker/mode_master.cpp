#include <Arduino.h>
#include "mode_master.h"
#include "resources.h"

ModeMaster::ModeMaster(Mode* initial_mode) : initial_mode(initial_mode) {
}

ModeMaster::~ModeMaster() {
}

void ModeMaster::setup() {
}
void ModeMaster::loop() {
  if (current_mode==NULL) {
    setModeUnlessNull(initial_mode);    
  }
  setModeUnlessNull(current_mode->loop());
}

void ModeMaster::setModeUnlessNull(Mode* mode) {
  if (mode != NULL) {
    if (current_mode != NULL) {
      current_mode->leave();
    }
    current_mode = mode;
    current_mode->enter();
  }
}

void ModeMaster::press() {
  setModeUnlessNull(current_mode->press());
}
void ModeMaster::longpress() {
  setModeUnlessNull(current_mode->longpress());
}
void ModeMaster::button_hold() {
  setModeUnlessNull(current_mode->button_hold());
}
void ModeMaster::left_turn() {
  setModeUnlessNull(current_mode->left_turn());
}
void ModeMaster::right_turn() {
  setModeUnlessNull(current_mode->right_turn());
}