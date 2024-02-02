#include "compass.h"
#include "MapComponent/stairs.h"

Compass::Compass(int row, int col): GameObject{row,col,ObjectType::Compass} {}

Compass::~Compass() {}

void Compass::setStair(Stairs *stair) { stairs = stair; }

void Compass::notifyStair() { stairs->notify(static_cast<Subject&>(*this)); }

void Compass::notify(Subject& whoFrom) {
    notifyObservers();
}
