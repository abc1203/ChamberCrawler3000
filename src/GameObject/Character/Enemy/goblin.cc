#include "goblin.h"

Goblin::Goblin(int row, int col): Enemy{row, col, EnemyType::Goblin,70,5,10} {}

// Goblin has the special skill of gold stealing
void Goblin::specialSkill(PlayerRace& target) {
    target.setGold(-1);
}
