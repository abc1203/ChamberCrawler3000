#ifndef TROLL_H
#define TROLL_H
#include "../enemy.h"

class Troll: public Enemy {
public:
    Troll(int row, int col);

    void specialSkill(PlayerRace& target) override;
};

#endif
