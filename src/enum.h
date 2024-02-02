#ifndef ENUM_H
#define ENUM_H
#include <iostream>
#include <string>

enum class Direction { NO, SO, EA, WE, NE, NW, SE, SW };
enum class ObjectType { HWall, VWall, Door, Passage, Tile, Stairs, Potion, Treasure, Compass, BarrierSuit, Enemy, Player, Weapon};
enum class EnemyType { Vampire, Werewolf, Goblin, Merchant, Dragon, Phoenix, Troll };
enum class PotionType { RH, BA, BD, PH, WA, WD };
enum class WeaponType { Sword, Armor };
enum class Attribute { Fire, Water };

std::ostream &operator<<(std::ostream &out, const Direction &ob);
std::ostream &operator<<(std::ostream &out, const ObjectType &ob);
std::ostream &operator<<(std::ostream &out, const PotionType &ob);
std::ostream &operator<<(std::ostream &out, const EnemyType &ob);
std::ostream &operator<<(std::ostream &out, const WeaponType &ob);
std::ostream &operator<<(std::ostream &out, const Attribute &ob);

#endif
