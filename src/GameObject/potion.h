#ifndef POTION_H
#define POTION_H
#include "../gameobject.h"


class Potion: public GameObject {
    PotionType potionType;
protected:
    Potion *component;
public:
    Potion(int row, int col, PotionType potionType);
    virtual ~Potion();
    virtual int getAtk(int atk, bool ifElves);
    virtual int getDef(int atk, bool ifElves);
    void setComponent(Potion* potions);
    PotionType getPotionType();
    
    void notify(Subject &whoFrom) override; // what does this do?
};


#endif
