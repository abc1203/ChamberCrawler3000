#ifndef MERCHANT_H
#define MERCHANT_H
#include "../enemy.h"


class Merchant: public Enemy {
public:
    Merchant(int row, int col);

    void setMerchantHostile(bool hostile);
    bool getMerchantHostile() const;

    // void specialSkill(PlayerRace& target) override;
};

#endif
