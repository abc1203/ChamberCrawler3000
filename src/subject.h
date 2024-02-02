#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "enum.h"

class Observer;

class Subject {
    std::vector<Observer*> observers;
    int row, col;
    ObjectType type;

public:
    void setRow(int newRow);
    void setCol(int newCol);
    void setObjectType(ObjectType newType);

    void attach(Observer *o);
    void notifyObservers();
    int getRow() const;
    int getCol() const;
    ObjectType getObjectType() const;
};

#endif
