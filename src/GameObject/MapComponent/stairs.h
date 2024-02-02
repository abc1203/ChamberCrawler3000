#ifndef STAIRS_H
#define STAIRS_H
#include "../mapcomponent.h"

class Stairs: public MapComponent {
    bool visibility;
public:
    Stairs(int row, int col);
    ~Stairs();
    void notify(Subject& whoFrom) override; // called from compass
    bool getVisibility();
    // void notifyObserver() override;
};


#endif
