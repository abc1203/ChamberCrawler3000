#include "WA.h"

WA::WA(int row, int col): Potion{row, col, PotionType::WA}{}

int WA::getAtk(int atk, bool ifElves){
    if(component != nullptr) atk = component->getAtk(atk,ifElves);
    if(ifElves) atk += 5;
    else if(atk-5 < 0) atk = 0; // make sure attack didn't go under zero
    else atk -= 5;
    return atk;
}

int WA::getDef(int def, bool ifElves){
    if(component != nullptr) def = component->getDef(def,ifElves);
    return def;
}
