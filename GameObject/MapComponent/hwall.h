#ifndef HWALL_H
#define HWALL_H
#include "../mapcomponent.h"

class HWall: public MapComponent {
public:
    HWall(int row, int col);
    ~HWall();
};


#endif
