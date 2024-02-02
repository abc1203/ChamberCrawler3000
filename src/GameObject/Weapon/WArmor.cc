#include "WArmor.h"

WArmor::WArmor(int row, int col): Weapon{row,col, WeaponType::Armor, Attribute::Water} {}
int WArmor::getDef(int def, Attribute attribute) {
    if(attribute != getAttribute()){ return 2 * def; }
    else return def;
}
