#include "treasure.h"

Treasure::Treasure(int row, int col, int value): GameObject{row,col,ObjectType::Treasure}, value{value} {
    if(value == 6) {
        available = false; // dragon horde not avaiable until dragon slained
    } else {
        available = true; // other hordes are free to pick up
    }
}

Treasure::~Treasure() {}

int Treasure::getValue() { return value; }

bool Treasure::isAvailable() { return available; }

void Treasure::notify(Subject &whoFrom) {
    if(whoFrom.getObjectType() == ObjectType::Enemy) { // dragon dies (i.e. called by enemy) => make horde available
        available = true;
    } 
}
