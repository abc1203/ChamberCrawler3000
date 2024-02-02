#ifndef FSWORD_H
#define FSWORD_H
#include "../weapon.h"

// Fire Sword
class FSword: public Weapon{
public:
    FSword(int row, int col);
    int getAtk(int atk, Attribute attribute) override;
};

#endif
