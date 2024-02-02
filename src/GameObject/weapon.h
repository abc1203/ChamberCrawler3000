#ifndef WEAPON_H
#define WEAPON_H
#include "../gameobject.h"


class Weapon: public GameObject {
    WeaponType weaponType;
    Attribute attribute;
public:
    Weapon(int row, int col, WeaponType weaponType, Attribute attribute);
    virtual ~Weapon();
    virtual int getAtk(int atk, Attribute attribute);
    virtual int getDef(int def, Attribute attribute);
    WeaponType getWeaponType();
    Attribute getAttribute();
    
    void notify(Subject &whoFrom) override;
};


#endif
