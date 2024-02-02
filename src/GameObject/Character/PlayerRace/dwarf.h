#ifndef DWARF_H
#define DWARF_H
#include "../playerrace.h"

class Dwarf: public PlayerRace {
public:
    Dwarf(int row, int col);

    void setGold(float amount) override;
};

#endif
