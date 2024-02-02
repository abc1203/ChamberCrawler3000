#ifndef GOBLIN_H
#define GOBLIN_H
#include "../enemy.h"

class Goblin: public Enemy {
public:
    Goblin(int row, int col);

    void specialSkill(PlayerRace& target) override;
};

#endif
