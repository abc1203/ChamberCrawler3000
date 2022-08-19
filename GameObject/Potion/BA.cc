#include "BA.h"

BA::BA(int row, int col): Potion{row, col, PotionType::BA}{}

int BA::getAtk(int atk, bool ifElves){
    if(component != nullptr) atk = component->getAtk(atk,ifElves);
    atk += 5;
    return atk;
}

int BA::getDef(int def, bool ifElves){
    if(component != nullptr) def = component->getDef(def,ifElves);
    return def;
}

