#ifndef WA_H
#define WA_H
#include "../potion.h"

class WA: public Potion{
public:
    WA(int row, int col);
    int getAtk(int atk, bool ifElves) override;
    int getDef(int atk, bool ifElves) override;
};

#endif
