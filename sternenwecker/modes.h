#ifndef MODES_H
#define MODES_H

#define MENU_COLOR matrix.Color(0, 100, 120)
#define TIME_COLOR matrix.Color(10, 2, 0) // regulate brightness via less color
#define TIME_SCROLL_STEP_DURATION 80
#define MENU_COUNT 4
#define TORCH_HUE_START 8
#define TORCH_HUE_STEPS 80
#define TORCH_BRIGHTNESS_MIN 1
#define TORCH_BRIGHTNESS_START 10
#define TORCH_BRIGHTNESS_STEPS 30
#define SET_COLOR matrix.Color(100, 0, 120)

// If a method which returns Mode* is called and it returns something non-NULL, the mode will be set after execution of the method.
class Mode {
  public:
    Mode();
    // if loop returns a Mode, the mode will be set by ModeMaster after completing this call.
    virtual Mode* loop() { return NULL; };
    // called when the sketch initializes
    virtual void init() {};
    // called when the state is entered
    virtual void enter() {};
    // called when the state is left
    virtual void leave() {};
    // called when the encoder button was pressed
    virtual Mode* press() { return NULL; };
    virtual Mode* longpress() { return NULL; };
    virtual Mode* button_hold() { return NULL; };
    // called when the encoder turned clockwise or counter-clockwise
    virtual Mode* left_turn() { return NULL; };
    virtual Mode* right_turn() { return NULL; };
};

class MOff : public Mode {
  public:
    MOff() : Mode() { };
    void enter();
    Mode* press();
};
extern MOff m_off;

class MTime : public Mode {
  public:
    MTime() : Mode() { };
    Mode* loop();
    void enter();
    void leave();
    Mode* press();
    Mode* longpress();
  private:
    unsigned long enter_millis;
};
extern MTime m_time;


class MMenu : public Mode {
  public:
    MMenu() : Mode() { };
    void enter();
    Mode* press();
    Mode* longpress();
    Mode* left_turn();
    Mode* right_turn();
  private:
    void update();
    uint8_t current;
};
extern MMenu m_menu;

class MTorch : public Mode {
  public:
    MTorch() : Mode() { };
    void enter();
    void leave();
    Mode* press();
    Mode* longpress();
    Mode* button_hold();
    Mode* left_turn();
    Mode* right_turn();
  private:
    void update();
    uint16_t hue;
    uint8_t brightness;
};
extern MTorch m_torch;

class MSetTime : public Mode {
  public:
    MSetTime() : Mode() { };
    void enter();
    Mode* loop();
    Mode* press();
    Mode* longpress();
    Mode* left_turn();
    Mode* right_turn();
  private:
    void update();
    uint8_t state;
};
extern MSetTime m_set_time;

#endif