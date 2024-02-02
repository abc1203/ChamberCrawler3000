#include "human.h"

Human::Human(int row, int col): PlayerRace{row,col,140,20,20} {}

float Human::getScore() { return 1.5*PlayerRace::getScore(); }


