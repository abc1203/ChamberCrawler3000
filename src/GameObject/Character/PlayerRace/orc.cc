#include "orc.h"

Orc::Orc(int row, int col): PlayerRace{row,col,180,30,25} {}

void Orc::setGold(float amount) { this->PlayerRace::setGold(amount / 2); }

