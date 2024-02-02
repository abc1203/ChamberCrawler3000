#ifndef WD_H
#define WD_H
#include "../potion.h"

class WD: public Potion{
public:
    WD(int row, int col);
    int getAtk(int atk, bool ifElves) override;
    int getDef(int atk, bool ifElves) override;
};

#endif
