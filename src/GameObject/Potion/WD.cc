#include "WD.h"

WD::WD(int row, int col): Potion{row,col,PotionType::WD} {}

int WD::getAtk(int atk, bool ifElves){
    if(component != nullptr) atk = component->getAtk(atk,ifElves);
    return atk;
}

int WD::getDef(int def, bool ifElves){
    if(component != nullptr) def = component->getDef(def,ifElves);
    if(ifElves) def += 5;
    else if(def-5 < 0) def = 0; // make sure attack didn't go under zero
    else def -= 5;
    return def;
}