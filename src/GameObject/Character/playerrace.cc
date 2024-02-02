#include "playerrace.h"
#include "../potion.h"
#include "../treasure.h"

PlayerRace::PlayerRace(int row, int col, int HP, int Atk, int Def): Character{row,col,ObjectType::Player,HP,Atk,Def}, goldAmount{0}, compass{false}, barrierSuit{false}, potion{nullptr}{}

PlayerRace::~PlayerRace(){ delete potion; }

void PlayerRace::setGold(float amount) { 
    goldAmount += amount; 
    if(goldAmount < 0) goldAmount = 0;
}

void PlayerRace::setCompass(bool compass) { this->compass = compass; }

void PlayerRace::setBarrierSuit(bool barrierSuit) { this->barrierSuit = barrierSuit; }

void PlayerRace::setPotion(Potion* newPotion) { 
    if(newPotion == nullptr) {
        std::cout << "wrong newpotion drink" << std::endl; return;
    } else if(newPotion->getPotionType() == PotionType::RH){
        if(getHP()+10 > getMaxHP()) setHP(getMaxHP()-getHP());
        else setHP(10);
        return;
    } else if(newPotion->getPotionType() == PotionType::PH){
        if(isImmune()) setHP(10);
        else setHP(-10);
        return;
    } else {
        if(potion == nullptr){
            potion = newPotion;
        }
        else{
            newPotion->setComponent(potion);
            potion = newPotion;
        }
    }
 }

void PlayerRace::clearPotion() { delete potion; potion = nullptr;}

bool PlayerRace::isImmune() { return false; }

float PlayerRace::getScore() { return goldAmount; }

int PlayerRace::getAtk(){
    int atk = getBaseAtk();
    if(potion == nullptr) return atk;
    atk = potion->getAtk(atk,isImmune());
    return atk;
}
int PlayerRace::getDef(){
    int def = getBaseDef();
    if(potion == nullptr) return def;
    def = potion->getDef(def,isImmune());
    return def;
}

float PlayerRace::getGold() { return goldAmount; }

Potion* PlayerRace::getPotion() { return potion; }

bool PlayerRace::hasCompass() { return compass; }

bool PlayerRace::hasBarrierSuit() { return barrierSuit; }

void PlayerRace::attack(Enemy& target) {
    float dmgCalc = (100 / (float)(100 + target.getDef())) * getAtk();
    int damage = std::ceil(dmgCalc);
    target.setHP((-1) * damage);
}

void PlayerRace::notify(Subject& whoFrom) {
    if(whoFrom.getObjectType() == ObjectType::Enemy) { // player kills an enemy; player gets one gold
        Enemy& enemy = static_cast<Enemy&>(whoFrom);

        if(enemy.getEnemyType() != EnemyType::Dragon && enemy.getEnemyType() != EnemyType::Merchant) {
            setGold(1);
        }
    } else if(whoFrom.getObjectType() == ObjectType::Treasure) { // player walks over a gold horde
        setGold((static_cast<Treasure&>(whoFrom)).getValue());
    } else if(whoFrom.getObjectType() == ObjectType::BarrierSuit) { // player walks over a barrier suit
        setBarrierSuit(true);
    } else if(whoFrom.getObjectType() == ObjectType::Compass) { // player walks over a compass
        setCompass(true);
    }
}
