#include "vampire.h"

Vampire::Vampire(int row, int col): Enemy{row, col, EnemyType::Vampire,50,25,25} {}

// Vampire has the special skill of health stealing
void Vampire::specialSkill(PlayerRace& target) {
    setHP(5);
    target.setHP(-5);
}
