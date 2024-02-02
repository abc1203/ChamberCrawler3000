#ifndef TREASURE_H
#define TREASURE_H
#include "../gameobject.h"

class Treasure: public GameObject {
    int value;
    bool available;
public:
    Treasure(int row, int col, int value);
    ~Treasure();
    int getValue();
    bool isAvailable();
    void notify(Subject &whoFrom); // called when a dragon dies => make horde availble
};


#endif
