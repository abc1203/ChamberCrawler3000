#include "barriersuit.h"

BarrierSuit::BarrierSuit(int row, int col): GameObject{row,col,ObjectType::BarrierSuit}, available{false} {}

BarrierSuit::~BarrierSuit() {}

bool BarrierSuit::isAvailable() const { return available; }

void BarrierSuit::notify(Subject &whoFrom) {
    if(whoFrom.getObjectType() == ObjectType::Enemy) { // dragon is slain
        available = true;
    } else std::cerr << "wrong notify to barrierSuit" << std::endl;
}
