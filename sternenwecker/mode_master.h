#ifndef MODE_MASTER_H
#define MODE_MASTER_H
#include "modes.h"

class ModeMaster {
   public:
     ModeMaster(Mode* initial_mode);
     ~ModeMaster();
     void setModeUnlessNull(Mode* mode);
     void setup();
     void loop();

     // see Mode class for more info on the following methods.
     // This class only delegates there and sets a new mode if needed.
     void press();
     void longpress();
     void left_turn();
     void right_turn();

     Mode* initial_mode;
     Mode* current_mode;
};

#endif