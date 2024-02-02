#include "merchant.h"

bool merchantHostile = false;

Merchant::Merchant(int row, int col): Enemy{row, col, EnemyType::Merchant,30,70,5} {}

void Merchant::setMerchantHostile(bool hostile) { merchantHostile = hostile; }

bool Merchant::getMerchantHostile() const { return merchantHostile; }

