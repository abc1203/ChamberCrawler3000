#include "dragon.h"

Dragon::Dragon(int row, int col): Enemy{row, col, EnemyType::Dragon,150,20,20} {}

// Dragon has the special skill of Burn: deal extra damage depending on player's defence
void Dragon::specialSkill(PlayerRace& target) {
    int burnDamage = std::ceil(0.3 * target.getDef());
    target.setHP((-1) * burnDamage);
}

void Dragon::setTreasure(GameObject* item) { this->guardItem = item; }

GameObject* Dragon::getTreasure() const { return guardItem; }
