#include "dwarf.h"

Dwarf::Dwarf(int row, int col): PlayerRace{row, col, 100,20,30} {}

void Dwarf::setGold(float amount) { this->PlayerRace::setGold(2 * amount); }


