#include "potion.h"
using namespace std;

Potion::Potion(int row, int col, PotionType pType): GameObject{row,col,ObjectType::Potion}, potionType{pType}, component{nullptr}{}

Potion::~Potion(){ delete component; }

void Potion::setComponent(Potion* potions) {
    if(component != nullptr) cerr << "Invalid Potion pipeline assginment" << endl;
    component = potions;
}

int Potion::getAtk(int atk, bool ifElves){
    cerr << "Incorrectly invoke potion's getAtk" << endl;
    return 0;
}

int Potion::getDef(int atk, bool ifElves){
    cerr << "Incorrectly invoke potion's getDef" << endl;
    return 0;
}

PotionType Potion::getPotionType(){ return potionType; }

void Potion::notify(Subject &whoFrom) {}

