#include "subject.h"
#include "observer.h"

void Subject::attach(Observer *o) {
    observers.emplace_back(o);
}

void Subject::notifyObservers() {
    for(auto &ob : observers) ob->notify(*this);
}

void Subject::setRow(int newRow) { row = newRow; }

int Subject::getRow() const { return row; }

void Subject::setCol(int newCol) { col = newCol; }

int Subject::getCol() const { return col; }

void Subject::setObjectType(ObjectType newType) { type = newType; }

ObjectType Subject::getObjectType() const { return type; }

