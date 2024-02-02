#include "FArmor.h"

FArmor::FArmor(int row, int col): Weapon{row,col, WeaponType::Armor, Attribute::Fire} {}
int FArmor::getDef(int def, Attribute attribute) {
    if(attribute != getAttribute()){ return 2 * def; }
    else return def;
}
