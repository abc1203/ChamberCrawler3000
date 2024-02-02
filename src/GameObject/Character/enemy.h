#ifndef ENEMY_H
#define ENEMY_H
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "../character.h"
#include "playerrace.h"

class PlayerRace;
class Compass;

class Enemy: public Character {
    EnemyType enemyType;
    bool hostile;
    Compass* compass;
    // maybe explicit show the ack and def in private
    // doing this allow we to strengthen or weaken the enemy thought the special skills of human.
    // for example when a knight fight with a devil, the devil is get weaken.
    // special feature considered later on


public:
    Enemy(int row, int col, EnemyType enemyType, int HP, int Atk, int Def); 
    ~Enemy();
    void setHostile(bool isHostile);
    bool isHostile() const;
    void setCompass(Compass* compass);
    Compass* getCompass(); 
    
    int getAtk();
    int getDef();
    EnemyType getEnemyType() const; 
    virtual void specialSkill(PlayerRace& target);
    void notify(Subject& whoFrom) override;

    void attack(PlayerRace& target); // could potentially be put in Character and have it overriden
    // still need a move/detectPlayer function - possibly using an observer
};

#endif
