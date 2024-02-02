#include "enemy.h"
#include "../compass.h"

Enemy::Enemy(int row, int col, EnemyType enemyType, int HP, int Atk, int Def): Character{row, col, ObjectType::Enemy, HP, Atk, Def}, enemyType{enemyType}, hostile{false}, compass{nullptr} {}

Enemy::~Enemy() {
    // std::cout << "enemy" << std::endl;
    delete compass;
}

void Enemy::setHostile(bool isHostile) { hostile = isHostile; }

bool Enemy::isHostile() const { return hostile; }

void Enemy::setCompass(Compass* compass) { this->compass = compass; }

Compass* Enemy::getCompass() { return compass; }

int Enemy::getAtk(){ return getBaseAtk(); }
int Enemy::getDef(){ return getBaseDef(); }

void Enemy::specialSkill(PlayerRace& target) {} 

EnemyType Enemy::getEnemyType() const { return enemyType; }

void Enemy::attack(PlayerRace& target) {
    float dmgCalc = (100 / (float)(100 + target.getDef())) * getAtk();
    int damage = std::ceil(dmgCalc);


    if(target.hasBarrierSuit()) {
        damage /= 2;
    } 
    target.setHP((-1) * damage);
}

void Enemy::notify(Subject& whoFrom) {}

