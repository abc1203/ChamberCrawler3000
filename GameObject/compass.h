#ifndef COMPASS_H
#define COMPASS_H
#include "../gameobject.h"

class Stairs;
class Enemy;

class Compass: public GameObject {
    Enemy* holder;
    Stairs* stairs; // don't have ownership
public:
    Compass(int row, int col);
    ~Compass();
    void setStair(Stairs *stair);
    void notifyStair();
    void notify(Subject& whoFrom) override;
};

#endif
