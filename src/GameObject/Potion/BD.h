#ifndef BD_H
#define BD_H
#include "../potion.h"

class BD: public Potion{
public:
    BD(int row, int col);
    int getAtk(int atk, bool ifElves) override;
    int getDef(int atk, bool ifElves) override;
};

#endif
