#include "gameobject.h"

GameObject::GameObject(int row, int col, ObjectType type) {
    setRow(row);
    setCol(col);
    setObjectType(type); // defines type for Subject
}

GameObject::~GameObject() {}

void GameObject::notify(Subject& whoFrom) {}
