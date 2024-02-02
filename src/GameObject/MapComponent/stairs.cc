#include "stairs.h"

Stairs::Stairs(int row, int col): MapComponent{row,col,ObjectType::Stairs}, visibility{false}{}

Stairs::~Stairs(){}

void Stairs::notify(Subject& whoFrom) {
    if(whoFrom.getObjectType() == ObjectType::Compass) {
        visibility = 1;
        notifyObservers();
    } else std::cerr << "wrong notify for stairs" << std::endl;
}

bool Stairs::getVisibility() { return visibility; }
