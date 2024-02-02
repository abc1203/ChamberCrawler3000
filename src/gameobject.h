#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <vector>
#include "observer.h"
#include "subject.h"
#include "textdisplay/textdisplay.h"
#include "enum.h"

class GameObject: public Observer, public Subject{

public:
    GameObject(int row, int col, ObjectType type);
    virtual ~GameObject();
    void notify(Subject& whoFrom) override;
};

#endif
