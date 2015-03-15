#ifndef MODES_H
#define MODES_H

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
    // called when the encoder turned clockwise or counter-clockwise
    virtual Mode* left_turn() { return NULL; };
    virtual Mode* right_turn() { return NULL; };
};

class MTest : public Mode {
  public:
    MTest() : Mode() { };
    void enter();
    Mode* loop();
    Mode* press();
    Mode* longpress();
    Mode* left_turn();
    Mode* right_turn();
};
extern MTest m_test;

#endif