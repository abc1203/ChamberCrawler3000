#include <cstdlib>
#include "game.h"
#include "floor.h"

Game::Game(string inputFile, bool givenMap) : floor{nullptr}, inputFile{inputFile}, givenMap{givenMap} {
    srand(time(0));
    barrierSuit = rand()%5;
}

Game::~Game() {
    delete floor;
}

void Game::play() {
    std::cin.exceptions(ios::eofbit|ios::failbit);
    string cmd, dir;
    try {
        floor = new Floor(inputFile, givenMap);
        // choosing Character
        char race = raceSelect();
        int n = diffSelect();

        floor->setBarrierSuit(barrierSuit);
        floor->raceSelect(race);
        floor->diffSelect(n);

        int floorNum = 0;
        while(floorNum < 5){
            floor->setFloorNum(floorNum);
            floor->newFloor();

            while(true) {
                floor->display();

                bool validCmd = false;
                do {
                    cin >> cmd;
                    if(isDirection(cmd)) {
                        validCmd = floor->move(getDirection(cmd));
                    } else if(cmd == "u") {
                        cin >> dir; 
                        if(isDirection(dir)) validCmd = floor->potion(getDirection(dir));
                    } else if(cmd == "a") {
                        cin >> dir; 
                        if(isDirection(dir)) validCmd = floor->attack(getDirection(dir));
                    } else if(cmd == "r") {
                        floorNum = 0;
                        floor->setFloorNum(floorNum);
                        race = raceSelect();
                        floor->raceSelect(race);
                        n = diffSelect();
                        floor->diffSelect(n);
                        floor->resetFile();
                        floor->newFloor();
                    } else if(cmd == "q") {
                        break; // might be OK to change to return
                    }
                    
                    if(validCmd) {
                        floor->gameTurn();
                    } else {
                        cout << "Please enter a valid command: " << endl;
                    }
                } while(!validCmd);

                // if floor ends
                if(floor->getFloorEnd()) {
                    // std::cout << "You have passed this floor." << std::endl;
                    break;
                }

                // if game ends
                if(floor->getGameEnd()) {
                    std::cout << "You died and the game has ended. Your score is: " << floor->getPlayerScore() << std::endl;
                    return;
                }
            }
            floorNum++;
        }
        std::cout << "Congraluations! You have won the game. Your score is: " << floor->getPlayerScore() << std::endl;
        
        
    } catch(ios::failure &) {} // Any I/O failure quits
}

bool Game::isDirection(string cmd) {
    if(cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" || cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw") return true;
    return false;
}

Direction Game::getDirection(string cmd) {
    if(cmd == "no") {
        return Direction::NO;
    } else if(cmd == "so") {
        return Direction::SO;
    } else if(cmd == "ea") {
        return Direction::EA;
    } else if(cmd == "we") {
        return Direction::WE;
    } else if(cmd == "ne") {
        return Direction::NE;
    } else if(cmd == "nw") {
        return Direction::NW;
    } else if(cmd == "se") {
        return Direction::SE;
    } else {
        return Direction::SW;
    }
}

char Game::raceSelect() {
    char race;
    cout << "Please choose your Character:" << endl;
    cout << "Character   HP      Atk     Def     Specialty" << endl;
    cout << "h: Human  140 HP  20 Atk  20 Def  No special skills." << endl;
    cout << "e: Elves  140 HP  30 Atk  10 Def  Negative potions have positive effect" << endl;
    cout << "d: Dwarf  100 HP  20 Atk  30 Def  Gold is doubled in value" << endl;
    cout << "o: Orc    180 HP  30 Atk  25 Def  Gold is worth half value" << endl;
    cout << "g: God    1000HP  500Atk  500Def  God is God" << endl; // hide the god
    cout << "Input one of following: h,e,d,o,g" << endl;
    while(cin >> race){
        if(race == 'h' || race == 'e' || race == 'd' || race == 'o' || race == 'g') break;
        cout << "Invalid choose of Character!" << endl;
        cout << "Please input one of following: h,e,d,o,g" << endl;
    }
    return race;
}

int Game::diffSelect() {
    int n;
    cout << "Please choose the Difficulty Level:" << endl;
    cout << "0:    Easy    10 Enemy each floor" << endl;
    cout << "1:   Normal   20 Enemy each floor" << endl;
    cout << "2:    Hard    30 Enemy each floor" << endl;
    cout << "3: Impossible 40 Enemy each floor" << endl;
    cout << "Input one of following: 0,1,2,3" << endl;
    while(cin >> n){
        if(n == 0 || n == 1 || n == 2 || n == 3) break;
        cout << "Invalid choose of Difficulty Level!" << endl;
        cout << "Please input one of following: 0,1,2,3" << endl;
    }
    return n;
}

