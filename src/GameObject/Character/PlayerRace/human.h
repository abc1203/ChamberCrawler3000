#ifndef HUMAN_H
#define HUMAN_H
#include "../playerrace.h"

class Human: public PlayerRace {
public:
    Human(int row, int col);
    float getScore() override;
};

#endif
