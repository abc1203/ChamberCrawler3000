#ifndef BARRIERSUIT_H
#define BARRIERSUIT_H
#include "../gameobject.h"

class BarrierSuit: public GameObject {
    bool available;
public:
    BarrierSuit(int row, int col);
    ~BarrierSuit();

    bool isAvailable() const;

    void notify(Subject &whoFrom) override;; // called when guarding dragon is slained => make available
};

#endif
