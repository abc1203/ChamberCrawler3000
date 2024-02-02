#include "elves.h"

Elves::Elves(int row, int col): PlayerRace{row, col, 140,30,10} {}

bool Elves::isImmune() { return true; }
