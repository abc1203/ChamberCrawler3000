#ifndef BA_H
#define BA_H
#include "../potion.h"

class BA: public Potion{
public:
    BA(int row, int col);
    int getAtk(int atk, bool ifElves) override;
    int getDef(int atk, bool ifElves) override;
    
    // void notify(Subject &whoFrom) override;
};

#endif
