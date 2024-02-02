#include "weapon.h"
using namespace std;

Weapon::Weapon(int row, int col, WeaponType weaponType, Attribute attribute): GameObject{row,col,ObjectType::Weapon}, weaponType{weaponType}, attribute{attribute} {}

Weapon::~Weapon(){}

WeaponType Weapon::getWeaponType() { return weaponType; }
Attribute Weapon::getAttribute() { return attribute; }

int Weapon::getAtk(int atk, Attribute attribute){ return atk; }
int Weapon::getDef(int def, Attribute attribute){ return def; }

void Weapon::notify(Subject &whoFrom) {}
