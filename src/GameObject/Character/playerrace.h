#ifndef PLAYERRACE_H
#define PLAYERRACE_H
#include <iostream>
#include "../character.h"
// #include "../potion.h"
// #include "../treasure.h"
// #include "../barriersuit.h"
#include "enemy.h"

class Enemy;
class Potion;
class Treasure;
class BarrierSuit;

class PlayerRace: public Character {
    float goldAmount;
    bool compass;
    bool barrierSuit;
    Potion *potion;

public:
    PlayerRace(int row, int col, int HP, int Atk, int Def);
    ~PlayerRace();

    virtual void setGold(float amount);
    void setCompass(bool compass);
    void setBarrierSuit(bool barrierSuit);
    void setPotion(Potion* newPotion);
    void clearPotion();
    virtual bool isImmune();
    virtual float getScore();
    
    int getAtk();
    int getDef();
    float getGold();
    Potion* getPotion();
    bool hasCompass();
    bool hasBarrierSuit();
    void attack(Enemy& target); // could potentially be put in Character and have it overriden
    void notify(Subject& whoFrom) override; // called when player kills an enemy; or when a player walks over loot
};

#endif
