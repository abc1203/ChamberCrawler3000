#include "troll.h"

Troll::Troll(int row, int col): Enemy{row, col, EnemyType::Troll,120,25,15} {}

// Trolls have the special skill of health regeneration
void Troll::specialSkill(PlayerRace& target) {
    setHP(7);
}
