#ifndef MODE_MASTER_H
#define MODE_MASTER_H
#include "modes.h"


class ModeMaster {
   public:
     ModeMaster(Mode* initial_mode);
     ~ModeMaster();
     void setModeUnlessNull(Mode* mode);
     void loop();

     Mode* initial_mode;
     Mode* current_mode;
};

#endif