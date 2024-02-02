#ifndef FARMOR_H
#define FARMOR_H
#include "../weapon.h"

// Fire Sword
class FArmor: public Weapon{
public:
    FArmor(int row, int col);
    int getDef(int def, Attribute attribute) override;
};

#endif
