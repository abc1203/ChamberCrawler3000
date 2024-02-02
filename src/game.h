#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <fstream>
#include <string>
#include "enum.h"
using namespace std;

class Floor;

class Game {
    Floor *floor;
    string inputFile;
    bool givenMap;
    int barrierSuit;
    char raceSelect();
    int diffSelect();
    void getManual();
    bool isDirection(string cmd);
    Direction getDirection(string cmd);
public:
    Game(string inputFile, bool givenMap);
    ~Game();
    void play();
};

#endif
