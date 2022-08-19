#ifndef PHOENIX_H
#define PHOENIX_H
#include "../enemy.h"

class Phoenix: public Enemy {
    bool reBorned;
public:
    Phoenix(int row, int col);

    // if a Phoenix dies, it is reborn with half the original max health and increased damage & decreased defense
    void reborn();
};

#endif