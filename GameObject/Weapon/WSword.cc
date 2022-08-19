#include "WSword.h"

WSword::WSword(int row, int col): Weapon{row,col, WeaponType::Sword, Attribute::Water} {}
int WSword::getAtk(int atk, Attribute attribute) {
    if(attribute != getAttribute()){ return 2 * atk; }
    else return atk;
}
