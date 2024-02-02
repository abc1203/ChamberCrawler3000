#ifndef DRAGON_H
#define DRAGON_H
#include "../enemy.h"

class Dragon: public Enemy {
    GameObject* guardItem;
public:
    Dragon(int row, int col);

    void setTreasure(GameObject* item);
    GameObject* getTreasure() const;
    void specialSkill(PlayerRace& target) override;
};

#endif
