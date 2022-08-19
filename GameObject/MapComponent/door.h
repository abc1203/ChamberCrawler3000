#ifndef DOOR_H
#define DOOR_H
#include "../mapcomponent.h"

class Door: public MapComponent {
public:
    Door(int row, int col);
    ~Door();
};


#endif
