#include "enum.h"

std::ostream &operator<<(std::ostream &out, const Direction &ob) {
    std::string s;
    if(ob == Direction::NW) s = "NW";
    else if(ob == Direction::NO) s = "NO";
    else if(ob == Direction::NE) s = "NE";
    else if(ob == Direction::WE) s = "WE";
    else if(ob == Direction::EA) s = "EA";
    else if(ob == Direction::SW) s = "SW";
    else if(ob == Direction::SO) s = "SO";
    else if(ob == Direction::SE) s = "SE";
    out << s;
    return out;
}

std::ostream &operator<<(std::ostream &out, const ObjectType &ob){
    std::string s;
    if(ob == ObjectType::HWall) s = "HWall";
    if(ob == ObjectType::VWall) s = "VWall";
    else if(ob == ObjectType::Door) s = "Door";
    else if(ob == ObjectType::Passage) s = "Passage";
    else if(ob == ObjectType::Tile) s = "Tile";
    else if(ob == ObjectType::Potion) s = "Potion";
    else if(ob == ObjectType::Treasure) s = "Treasure";
    else if(ob == ObjectType::Compass) s = "Compass";
    else if(ob == ObjectType::BarrierSuit) s = "BarrierSuit";
    else if(ob == ObjectType::Enemy) s = "Enemy";
    else if(ob == ObjectType::Player) s = "Player";
    out << s;
    return out;
}

std::ostream &operator<<(std::ostream &out, const PotionType &ob){
    std::string s;
    if(ob == PotionType::RH) s = "RH";
    else if(ob == PotionType::BA) s = "BA";
    else if(ob == PotionType::BD) s = "BD";
    else if(ob == PotionType::PH) s = "PH";
    else if(ob == PotionType::WA) s = "WA";
    else if(ob == PotionType::WD) s = "WD";
    out << s;
    return out;
}

std::ostream &operator<<(std::ostream &out, const EnemyType &ob){
    std::string s;
    if(ob == EnemyType::Vampire) s = "Vampire";
    else if (ob == EnemyType::Werewolf) s = "Werewolf";
    else if (ob == EnemyType::Goblin) s = "Goblin";
    else if (ob == EnemyType::Merchant) s = "Merchant";
    else if (ob == EnemyType::Dragon) s = "Dragon";
    else if (ob == EnemyType::Phoenix) s = "Phoenix";
    else if (ob == EnemyType::Troll) s = "Troll";
    out << s;
    return out;
}

std::ostream &operator<<(std::ostream &out, const WeaponType &ob){
    std::string s;
    if(ob == WeaponType::Sword) s = "Sword";
    else if(ob == WeaponType::Armor) s = "Armor";
    out << s;
    return out;
}

std::ostream &operator<<(std::ostream &out, const Attribute &ob){
    std::string s;
    if(ob == Attribute::Fire) s = "Fire";
    else if(ob == Attribute::Water) s = "Water";
    out << s;
    return out;
}
