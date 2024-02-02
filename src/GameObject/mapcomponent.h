#ifndef MAPCOMPONENT_H
#define MAPCOMPONENT_H
#include <iostream>
#include "../gameobject.h"

class MapComponent: public GameObject {
    int playerAccess, enemyAccess;

public:
    MapComponent(int row, int col, ObjectType type);
    ~MapComponent();
    void notify(Subject &whoFrom); // called when an character decides to move on top of it
};


#endif

