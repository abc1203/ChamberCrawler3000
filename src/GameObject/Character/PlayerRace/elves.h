#ifndef ELVES_H
#define ELVES_H
#include "../playerrace.h"

class Elves: public PlayerRace {
public:
    Elves(int row, int col);

    bool isImmune() override;
};

#endif
