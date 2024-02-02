#include "FSword.h"

FSword::FSword(int row, int col): Weapon{row,col, WeaponType::Sword, Attribute::Fire} {}
int FSword::getAtk(int atk, Attribute attribute) {
    if(attribute != getAttribute()){ return 2 * atk; }
    else return atk;
}
