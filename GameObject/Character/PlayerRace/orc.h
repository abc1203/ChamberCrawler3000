#ifndef ORC_H
#define ORC_H
#include "../playerrace.h"

class Orc: public PlayerRace {
public:
    Orc(int row, int col);
    void setGold(float amount) override;
};

#endif
