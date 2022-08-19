#ifndef FLOOR_H
#define FLOOR_H
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "gameobject.h"
#include "textdisplay/textdisplay.h"
#include "GameObject/Character/playerrace.h"
#include "GameObject/Character/enemy.h"
#include "GameObject/potion.h"
#include "GameObject/treasure.h"
#include "GameObject/Character/Enemy/dragon.h"


struct object{
    int row,col;
    GameObject *type;
    // char type;
}; 

class Floor {
    std::vector<std::vector<GameObject*>> grid;
    std::vector<std::vector<char>> graph;
    bool givenMap;
    std::fstream file;
    bool defaultFloor;
    std::string inputFile;
    // vector<vector<object>> cbound; // const, could be deleted
    std::vector<std::vector<object>> cgene; // const, used for newfloor, romoving odd and adding new
    std::vector<std::vector<object>> gene;
    std::vector<PotionType> potionKnown; // potion that player know
    int Prow, Pcol; // player's row and col
    TextDisplay *td; // textdisplay
    // list of observer of player needs to be updated each turn
    // including which object is in which direction
    PlayerRace *player;
    char pRace;
    int bs;
    int floorNum;
    bool floorEnd, gameEnd;
    std::stringstream action;
    int diffLevel; // 0 for easy, 1 for normal, 2 for difficult
    int enemyNum; // 10 for easy, 20 for normal, 30 for difficult
    void inputConvert();
    void findChamber(int row, int col, int chamber);
protected:
    GameObject* getDestination(Direction s); // returns player's selected destination; returns nullptr if the direction is invalid
    Direction getTargetDirection(int row, int col); // returns target's direction, given its row and col, relative to the player
public:
    Floor(std::string inputFile, bool givenMap);
    ~Floor();

    void newFloor();
    void reset();
    void setBarrierSuit(int BS);
    void raceSelect(char c);
    void diffSelect(int n);
    void resetFile();


    // following function return false if action is invalid
    // notify player when action is invalid
    bool move(Direction s);
    bool potion(Direction s);
    bool attack(Direction s);


    // invoke when player's action are valid
    // update the move first, then
    // update the list of observer, attach and detach when neccersary
    void gameTurn(); // enemies perform actions one by one
    void enemyTurn(Enemy* enemy); // a specific enemy performs actions

    // void reset();
    void display();
    void printTest();
    void setAction(std::string action, GameObject* target);

    // function for generating special stuff
    Potion* randomPotion(int row, int col);
    Treasure* randomTreasure(int row, int col);
    Enemy* randomEnemy(int row, int col);
    Dragon* geneDragon(int chamber, int row, int col);

    bool getFloorEnd();
    bool getGameEnd();
    float getPlayerScore();

    void setFloorNum(int num);
};

#endif
