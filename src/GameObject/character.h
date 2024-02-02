#ifndef CHARACTER_H
#define CHARACTER_H
#include <vector>
#include "../gameobject.h"


class Character: public GameObject {
    GameObject *previous;
    int HP, maxHP;
    int baseAtk;
    int baseDef;
    
public:
    Character(int row, int col, ObjectType type, int HP, int Atk, int Def);
    virtual ~Character();

    virtual int getBaseAtk();
    virtual int getBaseDef();
    // virtual void notify(Subject &whoFrom) = 0;

    bool isAlive();
    int getHP();
    int getMaxHP();
    
    void setAtk(int atk);
    void setDef(int def);
    void setHP(int amount);

    void setBaseAtk(int baseAtk);
    void setBaseDef(int baseDef);
    void setMaxHP(int maxHP);

    void setPrevious(GameObject* newPrev);
    GameObject* getPrevious() const;
};

// random generate some potion after death of enemy

#endif
