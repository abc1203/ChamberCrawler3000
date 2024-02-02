#ifndef WSWORD_H
#define WSWORD_H
#include "../weapon.h"

// Fire Sword
class WSword: public Weapon{
public:
    WSword(int row, int col);
    int getAtk(int atk, Attribute attribute) override;
};

#endif
