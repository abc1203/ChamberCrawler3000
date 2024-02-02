#ifndef VAMPIRE_H
#define VAMPIRE_H
#include "../enemy.h"

class Vampire: public Enemy {
public:
    Vampire(int row, int col);

    void specialSkill(PlayerRace& target) override;
};

#endif