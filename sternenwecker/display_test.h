#ifndef DISPLAY_TEST_H
#define DISPLAY_TEST_H

class MDisplayTest : public Mode {
  public:
    MDisplayTest() : Mode() { };
    void enter();
    Mode* loop();
    Mode* press();
    Mode* longpress();
    Mode* left_turn();
    Mode* right_turn();
  private:
    int8_t hour;
    int8_t min;
    int8_t current_test;
};
extern MDisplayTest m_display_test;

#endif