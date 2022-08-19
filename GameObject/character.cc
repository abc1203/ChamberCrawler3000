#include "character.h"
#include "MapComponent/tile.h"

Character::Character(int row, int col, ObjectType type, int HP, int Atk, int Def): GameObject{row,col,type}, previous{new Tile{row,col}}, HP{HP}, maxHP{HP}, baseAtk{Atk}, baseDef{Def} {}

Character::~Character(){
    // std::cout << "previous" << std::endl;
    delete previous;
    // std::cout << "after" << std::endl;
}
// when replace enemy to the ground permanent
// double check if the previous is deleted

int Character::getBaseAtk(){ return baseAtk; }
int Character::getBaseDef(){ return baseDef; }

bool Character::isAlive() {
    if(HP > 0) {
        return true;
    }
    return false;
}

int Character::getHP() { return HP; }
int Character::getMaxHP() { return maxHP; }

void Character::setAtk(int atk){ 
    baseAtk = atk;
    if(baseAtk < 0) baseAtk = 0;
}

void Character::setDef(int def){ 
    baseDef = def; 
    if(baseDef < 0) baseDef = 0;
}

void Character::setHP(int amount) { 
    HP += amount; 
    if(HP > maxHP) HP = maxHP;
    else if(HP < 0) HP = 0;
}

void Character::setMaxHP(int maxHP) { this->maxHP = maxHP; }

void Character::setPrevious(GameObject* newPrev) { previous = newPrev; }

GameObject* Character::getPrevious() const { return previous; }
