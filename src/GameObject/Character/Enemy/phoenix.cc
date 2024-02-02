#include "phoenix.h"

Phoenix::Phoenix(int row, int col): Enemy{row, col, EnemyType::Phoenix,50,35,20} {}


// if a Phoenix dies, it is reborn with half the original max health and increased damage & decreased defense
void Phoenix::reborn() {
    if(!isAlive()) {
        reBorned = true;
        setMaxHP(25);
        setHP(25);
        setAtk(50);
        setDef(10);
    }
}
