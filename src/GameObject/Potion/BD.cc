#include "BD.h"

BD::BD(int row, int col): Potion{row, col, PotionType::BD}{}

int BD::getAtk(int atk, bool ifElves){
    if(component != nullptr) atk = component->getAtk(atk,ifElves);
    return atk;
}

int BD::getDef(int def, bool ifElves){
    if(component != nullptr) def = component->getDef(def,ifElves);
    def += 5;
    return def;
}
