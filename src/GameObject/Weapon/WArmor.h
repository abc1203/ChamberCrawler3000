#ifndef WARMOR_H
#define WARMOR_H
#include "../weapon.h"

// Fire Sword
class WArmor: public Weapon{
public:
    WArmor(int row, int col);
    int getDef(int atk, Attribute attribute) override;
};

#endif
