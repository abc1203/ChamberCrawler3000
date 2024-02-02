#ifndef VWALL_H
#define VWALL_H
#include "../mapcomponent.h"

class VWall: public MapComponent {
public:
    VWall(int row, int col);
    ~VWall();
};


#endif
