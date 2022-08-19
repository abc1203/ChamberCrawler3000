#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream>
#include "floor.h"
#include "GameObject/character.h"
#include "GameObject/Character/PlayerRace/dwarf.h"
#include "GameObject/Character/PlayerRace/elves.h"
#include "GameObject/Character/PlayerRace/human.h"
#include "GameObject/Character/PlayerRace/orc.h"
#include "GameObject/Character/PlayerRace/god.h"

#include "GameObject/Character/Enemy/goblin.h"
#include "GameObject/Character/Enemy/merchant.h"
#include "GameObject/Character/Enemy/phoenix.h"
#include "GameObject/Character/Enemy/troll.h"
#include "GameObject/Character/Enemy/vampire.h"
#include "GameObject/Character/Enemy/werewolf.h"

#include "GameObject/Potion/RH.h"
#include "GameObject/Potion/PH.h"
#include "GameObject/Potion/BA.h"
#include "GameObject/Potion/BD.h"
#include "GameObject/Potion/WA.h"
#include "GameObject/Potion/WD.h"

#include "GameObject/mapcomponent.h"
#include "GameObject/MapComponent/hwall.h"
#include "GameObject/MapComponent/vwall.h"
#include "GameObject/MapComponent/door.h"
#include "GameObject/MapComponent/passage.h"
#include "GameObject/MapComponent/tile.h"
#include "GameObject/MapComponent/stairs.h"

#include "GameObject/compass.h"
#include "GameObject/barriersuit.h"
using namespace std;


Floor::Floor(string inputFile, bool givenMap): givenMap{givenMap}, inputFile{inputFile}, Prow{-1}, Pcol{-1}, td{new TextDisplay()}, pRace{'c'}, bs{false}, floorNum{0}, floorEnd{false}, gameEnd{false}, action{"Player Character has spawned"}, diffLevel{1}, enemyNum{20} {
    file.open(inputFile);
    // initialize graph to be empty
    // vector<vector<char>> graph;
    for(int i=0;i<25;++i){
        vector<GameObject *> ob;
        // vector<char> g;
        for(int j=0;j<79;++j){
            ob.emplace_back(nullptr);
            // g.emplace_back(' ');
        }
        grid.emplace_back(ob);
        // graph.emplace_back(g);
    }

    for(int k=0;k<5;++k){
        vector<object> v1;
        gene.push_back(v1);
    }
}

Floor::~Floor() {
    for(auto vec: grid){
        for(auto ob: vec){
            if(ob != nullptr && ob->getObjectType() != ObjectType::Player){
                delete ob;
            }
            ob = nullptr;
        }
    }
    delete td;
    delete player;
}

void Floor::inputConvert(){
    for(int i=0;i<25;++i){
        vector<char> vec;
        for(int j=0;j<79;++j){
            vec.emplace_back(' ');
        }
        graph.emplace_back(vec);
    }

    char c;
    for(int i=0;i<25;++i){
        string s;
        getline(file,s);
        istringstream ss{s};
        for(int j=0;j<79;++j){
            ss.get(c);
            if(c == '.') graph[i][j] = '.';
            else if(c == '-'){
                grid[i][j] = new HWall{i,j};
                grid[i][j]->attach(td);
                grid[i][j]->notifyObservers();
            }
            else if(c == '|'){
                grid[i][j] = new VWall{i,j};
                grid[i][j]->attach(td);
                grid[i][j]->notifyObservers();
            }
            else if(c == '+'){
                grid[i][j] = new Door{i,j};
                grid[i][j]->attach(td);
                grid[i][j]->notifyObservers();
            }
            else if(c == '#'){
                grid[i][j] = new Passage{i,j};
                grid[i][j]->attach(td);
                grid[i][j]->notifyObservers();
            }
        }
    }

    int chamber = 0;
    for(int i=1;i<24;++i){
        for(int j=1;j<78;++j){
            if(graph[i][j] == ' ') continue;
            else if(graph[i][j] == '.'){
                findChamber(i,j,chamber);
                chamber++;
            }
            else cerr << "weird input" << endl;
        }
    }
    cgene = gene;
}

void Floor::findChamber(int row, int col, int chamber){
    for(int i=row-1;i<=row+1;++i){
        for(int j=col-1;j<=col+1;++j){
            if(i == row && j == col) continue;
            else if(graph[i][j] == ' ') continue;
            else if(graph[i][j] == '.'){
                graph[i][j] = ' ';
                object ob{i,j,nullptr};
                gene[chamber].emplace_back(ob);
                findChamber(i,j,chamber);
            }
            else {
                cerr << graph[i][j] << "hello" << endl;
                // cerr << "weird chamber" << endl;
            }
        }
    }
}



void Floor::newFloor(){
    // potionKnown.clear();
    floorEnd = false;
    gameEnd = false;

    // romoving old object (stuff inside the chamber)
    for(auto vec:gene){
        for(auto ob:vec){
            if(grid[ob.row][ob.col] != nullptr && grid[ob.row][ob.col]->getObjectType() != ObjectType::Player){
                delete grid[ob.row][ob.col];
            }
            grid[ob.row][ob.col] = nullptr;
        }
    }
    td->clean();

    if(givenMap){
        // bool ifPlayer = false;
        char c;
        for(int i=0;i<25;++i){
            string s;
            getline(file,s);
            istringstream ss{s};
            for(int j=0;j<79;++j){
                if(grid[i][j] != nullptr && grid[i][j]->getObjectType() != ObjectType::Player) delete grid[i][j];
                ss.get(c);
                // cout << c;
                if(c == '-') grid[i][j] = new HWall{i,j};
                else if(c == '|') grid[i][j] = new VWall{i,j};
                else if(c == '+') grid[i][j] = new Door{i,j};
                else if(c == '#') grid[i][j] = new Passage{i,j};
                else if(c == '.') grid[i][j] = new Tile{i,j};
                else if(c == '\\'){
                    Stairs* stair = new Stairs{i,j};
                    Compass* compass = new Compass{-1,-1};
                    stair->notify(*compass);
                    delete compass;
                    grid[i][j] = stair;
                }
                else if(c == '0') grid[i][j] = new RH{i,j};
                else if(c == '1') grid[i][j] = new BA{i,j};
                else if(c == '2') grid[i][j] = new BD{i,j};
                else if(c == '3') grid[i][j] = new PH{i,j};
                else if(c == '4') grid[i][j] = new WA{i,j};
                else if(c == '5') grid[i][j] = new WD{i,j};
                else if(c == '6') grid[i][j] = new Treasure{i,j,1};
                else if(c == '7') grid[i][j] = new Treasure{i,j,2};
                else if(c == '8') grid[i][j] = new Treasure{i,j,4};
                else if(c == '9') grid[i][j] = new Treasure{i,j,6};
                else if(c == 'V' || c == 'W' || c == 'N' || c == 'M' || c == 'D' || c == 'X' || c == 'T') {
                    Enemy* enemy;
                    if(c == 'V') enemy = new Vampire{i,j};
                    else if(c == 'W') enemy = new Werewolf{i,j};
                    else if(c == 'N') enemy = new Goblin{i,j};
                    else if(c == 'M') enemy = new Merchant{i,j};
                    else if(c == 'D') enemy = new Dragon{i,j};
                    else if(c == 'X') enemy = new Phoenix{i,j};
                    else if(c == 'T') enemy = new Troll{i,j};
                    enemy->getPrevious()->attach(td);
                    grid[i][j] = enemy;
                }

                else if(c == '@') {
                    Prow = i;
                    Pcol = j;
                    grid[Prow][Pcol] = player;
                    player->setRow(Prow);
                    player->setCol(Pcol);
                    player->clearPotion();
                    delete player->getPrevious();
                    player->setPrevious(new Tile{Prow,Pcol});
                    player->getPrevious()->attach(td);
                    player->getPrevious()->setRow(Prow);
                    player->getPrevious()->setCol(Pcol);
                    player->getPrevious()->notifyObservers();
                    player->notifyObservers();
                }
                else if(c == ' ') continue;
                else continue;
                grid[i][j]->attach(td);
                grid[i][j]->notifyObservers();

            }
            // cout << endl;
        }
        return;
    }

    inputConvert();

    // adding new object
    // start generation

    int enemy = enemyNum; // number of enemy needs to be generate
    int row, col;

    // shuffle all the title in each chamber
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    for(int k=0;k<5;++k) shuffle( gene[k].begin(), gene[k].end(), rng );

    int p;
    // generate player's position
    player->clearPotion();

    srand(seed);
    p = rand()%5; 
    Prow = gene[p][0].row;
    Pcol = gene[p][0].col;
    grid[Prow][Pcol] = player;
    player->setRow(Prow);
    player->setCol(Pcol);
    player->clearPotion(); // clear the Potion drink in the previous floor
    delete player->getPrevious();
    player->setPrevious(new Tile{Prow,Pcol});
    player->getPrevious()->attach(td);
    player->getPrevious()->setRow(Prow);
    player->getPrevious()->setCol(Pcol);

    player->getPrevious()->notifyObservers();
    player->notifyObservers();
    // graph[Prow][Pcol] = '@';
    gene[p].erase(gene[p].begin());

    // generate stair's position
    int q = rand()%5;
    while(q == p){
        q = rand()%5;
    }
    row = gene[q][0].row;
    col = gene[q][0].col;
    Stairs *stair = new Stairs(row,col);
    // cout << row << " " << col << endl;
    grid[row][col] = stair;
    grid[row][col]->attach(td);
    grid[row][col]->notifyObservers();
    // graph[gene[p][0].row][gene[p][0].col] = '\\';
    gene[q].erase(gene[q].begin());

    // generate barrierSuit's position
    if(bs == floorNum){
        p = rand()%5;
        row = gene[p][0].row;
        col = gene[p][0].col;
        grid[row][col] = new BarrierSuit(row,col);
        grid[row][col]->attach(td);
        grid[row][col]->notifyObservers();
        // graph[gene[p][0].row][gene[p][0].col] = '\\';
        int brow = gene[p][0].row;
        int bcol = gene[p][0].col;
        gene[p].erase(gene[p].begin());

        Dragon* dragon = geneDragon(p,brow,bcol);
        dragon->setTreasure(dynamic_cast<GameObject*>(grid[gene[p][0].row][gene[p][0].col]));

        --enemy;
    }

    // generate potion
    for(int k=0;k<10;++k){
        p = rand()%5;
        int row = gene[p][0].row;
        int col = gene[p][0].col;
        grid[row][col] = randomPotion(row,col);
        grid[row][col]->attach(td);
        grid[row][col]->notifyObservers();
        gene[p].erase(gene[p].begin());
    }
    
    // generate treasure
    for(int k=0;k<10;++k){
        p = rand()%5;
        int grow = gene[p][0].row;
        int gcol = gene[p][0].col;
        Treasure* treasure = randomTreasure(grow,gcol);
        int value = treasure->getValue();
        grid[grow][gcol] = treasure;
        grid[grow][gcol]->attach(td);
        grid[grow][gcol]->notifyObservers();
        //generate dragon to garde for dragon hoard
        gene[p].erase(gene[p].begin());
        if(value == 6){
            Dragon* dragon = geneDragon(p,grow,gcol);
            dragon->setTreasure(dynamic_cast<GameObject*>(grid[gene[p][0].row][gene[p][0].col]));
            --enemy;
        }
    }
    
    // generate enemy
    int compass = rand()%enemy;
    for(int k=0;k<enemy;++k){
        p = rand()%5;
        row = gene[p][0].row;
        col = gene[p][0].col;
        Enemy* enemy= randomEnemy(row,col);
        grid[row][col] = enemy;
        grid[row][col]->attach(td);
        grid[row][col]->notifyObservers();

        if(k == compass){
            Compass* compass = new Compass(row,col);
            enemy->setCompass(compass);
            compass->attach(td);
            compass->setStair(stair);
            // grid[row][col]->attach(compass);
        } // bind the compass to the enemy
        gene[p].erase(gene[p].begin());

    }

    // fill the rest with floor tile;
    for(int k=0;k<5;++k){
        for(auto ob: gene[k]){
            grid[ob.row][ob.col] = new Tile{ob.row,ob.col};
            grid[ob.row][ob.col]->attach(td);
            grid[ob.row][ob.col]->notifyObservers();
        }
    }

    // refreshing the gene to be cgene
    gene = cgene;
}


void Floor::raceSelect(char c) {
    pRace = c;
    delete player;
    if(c == 'h') player = new Human{Prow,Pcol};
    else if(c == 'e') player = new Elves{Prow,Pcol};
    else if(c == 'd') player = new Dwarf{Prow,Pcol};
    else if(c == 'o') player = new Orc{Prow,Pcol};
    else if(c == 'g') player = new God{Prow,Pcol};
    else cerr << "Incorrect Race Selection" << endl;
    player->attach(td);
    player->getPrevious()->attach(td);
}

void Floor::diffSelect(int n){
    diffLevel = n;
    if(n == 0) enemyNum = 10;
    else if(n == 1) enemyNum = 20;
    else if(n == 2) enemyNum = 30;
    else if(n == 3) enemyNum = 40;
}

void Floor::resetFile(){
    file.close();
    file.open(inputFile);
}

GameObject* Floor::getDestination(Direction s) {
    int destRow, destCol;
    // finds the expected destination
    if(s == Direction::NO) { // north
        destRow = player->getRow() - 1; destCol = player->getCol();
    } else if(s == Direction::SO) { // south
        destRow = player->getRow() + 1; destCol = player->getCol();
    } else if(s == Direction::EA) { // east
        destRow = player->getRow(); destCol = player->getCol() + 1;
    } else if(s == Direction::WE) { // west
        destRow = player->getRow(); destCol = player->getCol() - 1;
    } else if(s == Direction::NE) { // northeast
        destRow = player->getRow() - 1; destCol = player->getCol() + 1;
    } else if(s == Direction::NW) { // northwest
        destRow = player->getRow() - 1; destCol = player->getCol() - 1;
    } else if(s == Direction::SE) { // southeast
        destRow = player->getRow() + 1; destCol = player->getCol() + 1;
    } else if(s == Direction::SW) { // southwest
        destRow = player->getRow() + 1; destCol = player->getCol() - 1;
    }

    if((destRow >= 0 && destRow < (int)grid.size()) && (destCol >= 0 && destCol < (int)grid[destRow].size()) && grid[destRow][destCol] != nullptr) {
        return grid[destRow][destCol];
    }
    return nullptr;
}

Direction Floor::getTargetDirection(int row, int col) {
    if(row == player->getRow() && col < player->getCol()) return Direction::WE;
    else if(row == player->getRow() && col > player->getCol()) return Direction::EA;
    else if(row < player->getRow() && col == player->getCol()) return Direction::NO;
    else if(row > player->getRow() && col == player->getCol()) return Direction::SO;
    else if(row < player->getRow() && col < player->getCol()) return Direction::NW;
    else if(row < player->getRow() && col > player->getCol()) return Direction::NE;
    else if(row > player->getRow() && col < player->getCol()) return Direction::SW;
    else return Direction::SE;
}


// player moves; return false if the move is invalid
bool Floor::move(Direction s) {
    GameObject* destination = getDestination(s);

    if(destination != nullptr && 
    (destination->getObjectType() != ObjectType::HWall && destination->getObjectType() != ObjectType::VWall &&
    destination->getObjectType() != ObjectType::Potion && 
    destination->getObjectType() != ObjectType::Enemy && 
    destination->getObjectType() != ObjectType::Player)) { // player moves

        if((destination->getObjectType() == ObjectType::Treasure && !(dynamic_cast<Treasure*>(destination)->isAvailable())) ||
           (destination->getObjectType() == ObjectType::BarrierSuit && !(dynamic_cast<BarrierSuit*>(destination)->isAvailable()))) {
            return false;
        } else {
            setAction("move", destination);

            player->getPrevious()->notify(*player); // set up the location for the tile player was holding
            grid[player->getRow()][player->getCol()] = player->getPrevious(); // drops the original tile on the grid
            player->getPrevious()->notifyObservers();

            // player moves
            player->setPrevious(destination);
            player->setRow(destination->getRow());
            player->setCol(destination->getCol());
            grid[player->getRow()][player->getCol()] = player;
            player->notifyObservers();

            // player stepped on an available horde/barrier suit/compass => pick it up
            ObjectType type = player->getPrevious()->getObjectType();
            if(type == ObjectType::Treasure || type == ObjectType::BarrierSuit || type == ObjectType::Compass) {
                setAction("collect", player->getPrevious());

                player->notify(dynamic_cast<Subject&>(*(player->getPrevious()))); // player picks up the item
                if(type == ObjectType::Compass){
                    Compass* compass = dynamic_cast<Compass*>(player->getPrevious());
                    compass->notifyStair();
                } // compass makes stairs visible
                delete player->getPrevious(); // deletes the item
                player->setPrevious(new Tile{player->getRow(), player->getCol()}); // sets a new tile
                player->getPrevious()->attach(td);
            } 

            bool attacked = false;
            // check if there are any non-merchant enemies surrounding player => attack if there is
            for(int i = player->getRow()-1; i <= player->getRow()+1; ++i) {
                for(int j = player->getCol()-1; j <= player->getCol()+1; ++j) {
                    if(grid[i][j] != nullptr) {
                        if(grid[i][j]->getObjectType() == ObjectType::Enemy && dynamic_cast<Enemy*>(grid[i][j])->getEnemyType() != EnemyType::Merchant && !attacked) {
                            attack(getTargetDirection(i, j));
                            attacked = true;
                        } else if(grid[i][j]->getObjectType() == ObjectType::Potion || grid[i][j]->getObjectType() == ObjectType::Treasure ||
                                grid[i][j]->getObjectType() == ObjectType::Compass || grid[i][j]->getObjectType() == ObjectType::BarrierSuit) {
                            setAction("see", grid[i][j]);
                        }
                    }
                }
            }

            // player stepped on the stairs => immediately goes to the next floor
            if(type == ObjectType::Stairs) {
                setAction("nextFloor", player->getPrevious());
                floorEnd = true;
            }
            return true;
        }
    }
    return false;
}


// player drinks the potion; return false if the action is invalid
bool Floor::potion(Direction s) {
    GameObject* target = getDestination(s);

    if(target != nullptr && target->getObjectType() == ObjectType::Potion) {
        // player drinks the potion
        Potion* potion = dynamic_cast<Potion*>(target);
        player->setPotion(potion);
        // cout << potion->getPotionType() << endl;
        // if(player->getPotion() == nullptr) cout << "drink fail"  << endl;
        // potion disappears
        int prow = potion->getRow(); int pcol = potion->getCol();
        grid[prow][pcol] = new Tile{prow,pcol};
        grid[prow][pcol]->attach(td);
        grid[prow][pcol]->notifyObservers();

        setAction("drink", potion);
        if(potion->getPotionType() == PotionType::RH || potion->getPotionType() == PotionType::PH) delete potion;
        return true;
    }
    return false;
}


// player attacks; return false if the attack is invalid
bool Floor::attack(Direction s) {
    GameObject* target = getDestination(s);

    if(target != nullptr && target->getObjectType() == ObjectType::Enemy) {
        // player attacks the enemy
        Enemy* enemy = dynamic_cast<Enemy*>(target);
        player->attack(*enemy);

        // makes all merchants hostile if player attacked a merchant
        if(enemy->getEnemyType() == EnemyType::Merchant) {
            dynamic_cast<Merchant*>(enemy)->setMerchantHostile(true);
        }

        setAction("attackEnemy", enemy);

        // player kills the enemy
        if(!(enemy->isAlive())) {
            // if enemy is a dragon, notifies its treasure so that it can be picked up
            enemy->notifyObservers();

            enemy->getPrevious()->notify(*enemy); // set up dropped tile location
            grid[enemy->getRow()][enemy->getCol()] = enemy->getPrevious();
            enemy->getPrevious()->notifyObservers();

            player->notify(*enemy); // player collects gold from enemy death

            setAction("killEnemy", enemy);

            // merchant drops a gold horde upon death
            if(enemy->getEnemyType() == EnemyType::Merchant) { 
                int row = enemy->getRow(); int col = enemy->getCol();
                delete grid[row][col]; // deletes the old tile on the floor
                grid[row][col] = new Treasure{row, col, 4}; // puts merchant horde on the floor
                grid[row][col]->attach(td);
                grid[row][col]->notifyObservers();

                setAction("see", grid[row][col]);
            } 
            
            if(enemy->getCompass() != nullptr) { // the killed enemy is the holder of the compass => drops the compass
                int row = enemy->getRow(); int col = enemy->getCol();
                enemy->getCompass()->setRow(row); enemy->getCompass()->setCol(col);
                delete grid[row][col]; // deletes the old tile on the floor
                grid[row][col] = enemy->getCompass(); // places the compass on the floor
                grid[row][col]->notifyObservers();

                setAction("see", grid[row][col]);
            } 
            enemy->setPrevious(nullptr);
            enemy->setCompass(nullptr);
            delete enemy;
        }   
        return true;
    }
    return false;
}


void Floor::gameTurn() {
    std::vector<Enemy*> enemies;
    // scan for any enemies
    for(int i = 0; i < (int)grid.size(); ++i) {
        for(int j = 0; j < (int)grid[i].size(); ++j) {
            if(grid[i][j] != nullptr && grid[i][j]->getObjectType() == ObjectType::Enemy) {
                enemies.emplace_back(dynamic_cast<Enemy*>(grid[i][j]));
            }
        }
    }

    // enemies performs action one-by-one
    for(int i = 0; i < (int)enemies.size(); ++i) enemyTurn(enemies[i]);
}

// an individual enemy performs action
void Floor::enemyTurn(Enemy* enemy) {
    bool hostileFlag = false;
    
    // check if player is nearby; set hostile to true in that case
    for(int i = enemy->getRow()-1; i <= enemy->getRow()+1; ++i) {
        for(int j = enemy->getCol()-1; j <= enemy->getCol()+1; ++j) {
            if((i >= 0 && i < (int)grid.size()) && (j >= 0 && j <= (int)grid[i].size()) && grid[i][j] != nullptr && grid[i][j]->getObjectType() == ObjectType::Player) {
                enemy->setHostile(true);
                hostileFlag = true;
            }
        }
    }
    if(!hostileFlag) enemy->setHostile(false);

    if(enemy->isHostile()) { // attacks player if in range, unless it is a non-hostile merchant
        if(!(enemy->getEnemyType() == EnemyType::Merchant && !((dynamic_cast<Merchant*>(enemy))->getMerchantHostile()))) {
            // determine if attack lands using shuffle
            std::vector<int> v = {0, 1};
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine rng{seed};
            for(int i = 0; i < 100; ++i) std::shuffle(v.begin(), v.end(), rng);

            if(v[0] == 1) { // the attack lands
                enemy->attack(*player);
                setAction("attackPlayer", enemy);
            } else {
                setAction("missPlayer", enemy);
            }
            // special skill activates regardless of whether the attack lands
            enemy->specialSkill(*player);
        }
        // enemy kills the player => game ends
        if(!(player->isAlive())) {
            gameEnd = true;
            setAction("killPlayer", enemy);
            return;
        }
    } else if(enemy->getEnemyType() != EnemyType::Dragon) { // moves unless it is a dragon
        // finds the available destinations
        std::vector<GameObject*> possibleDestinations;

        for(int i = enemy->getRow()-1; i <= enemy->getRow()+1; ++i) {
            for(int j = enemy->getCol()-1; j <= enemy->getCol()+1; ++j) {
                if(grid[i][j] != nullptr && grid[i][j]->getObjectType() == ObjectType::Tile) {
                    possibleDestinations.emplace_back(grid[i][j]);
                }
            }
        }
        
        if(possibleDestinations.size() != 0) {
            // randomly chooses a destination using shuffle
            unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine rng{seed};
            for(int i = 0; i < 1000; ++i) {
                std::shuffle(possibleDestinations.begin(), possibleDestinations.end(), rng);
            }

            // performs the move
            enemy->getPrevious()->notify(dynamic_cast<Subject&>(*enemy)); // drops the tile at the original location
            grid[enemy->getRow()][enemy->getCol()] = enemy->getPrevious();
            enemy->getPrevious()->notifyObservers();

            enemy->setPrevious(possibleDestinations[0]); // picks up the new tile
            enemy->setRow(possibleDestinations[0]->getRow()); // updates row location for enemy
            enemy->setCol(possibleDestinations[0]->getCol()); // updates col location for enemy
            grid[enemy->getRow()][enemy->getCol()] = enemy;
            enemy->notifyObservers();
        }
    }
}

void Floor::setBarrierSuit(int BS) { bs = BS; }
void Floor::setFloorNum(int num) { floorNum = num; }

Potion* Floor::randomPotion(int row, int col){
    // type of potion: 1/6 chance each
    Potion* potion;
	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    int p = rand()%6;
    if(p == 0) potion = new RH{row,col};
    else if(p == 1) potion = new PH{row,col};
    else if(p == 2) potion = new BA{row,col};
    else if(p == 3) potion = new BD{row,col};
    else if(p == 4) potion = new WA{row,col};
    else if(p == 5) potion = new WD{row,col};
    else cerr << "Incorrect random Potion" << endl;
    return potion;
}


Treasure* Floor::randomTreasure(int row, int col){
    // type of treasure: 5/8 normal, 1/8 dragon hoard, 1/4 small horde
    Treasure* treasure;
	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    int p = rand()%8;
    if(0 <= p && p < 5) treasure = new Treasure{row,col,1};
    else if(5 <= p && p < 6) treasure = new Treasure{row,col,6};
    else if(6 <= p && p < 8) treasure = new Treasure{row,col,2};
    else cerr << "Incorrect random Treasure" << endl;
    return treasure;
}

Enemy* Floor::randomEnemy(int row, int col){
    // type of enemy: Werewolf: 2/9, Vampire: 3/18, Goblin: 5/18, Troll: 1/9, Phoenix: 1/9, Merchant: 1/9
    Enemy* enemy;
	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    int p = rand()%18;
    if(0 <= p && p < 4) enemy = new Werewolf{row,col};
    else if(4 <= p && p < 7) enemy = new Vampire{row,col};
    else if(7 <= p && p < 12) enemy = new Goblin{row,col};
    else if(12 <= p && p < 14) enemy = new Troll{row,col};
    else if(14 <= p && p < 16) enemy = new Phoenix{row,col};
    else if(16 <= p && p < 18) enemy = new Merchant{row,col};
    else cerr << "Incorrect random Enemy" << endl;
    enemy->getPrevious()->attach(td);
    return enemy;
}

Dragon* Floor::geneDragon(int chamber, int row, int col){
    // generate dragon to guard
    vector<object> availabe; // available for dragon
    for (auto ob = gene[chamber].begin(); ob != gene[chamber].end();){
        if(abs(row - ob->row) <= 1 && abs(col - ob->col) <= 1){
            availabe.push_back(*ob);
            ob = gene[chamber].erase(ob);
        }
        else{
            ++ob;
        }
    }
    int q = rand() % availabe.size();
    int drow = availabe[q].row;
    int dcol = availabe[q].col;
    grid[drow][dcol] = new Dragon{drow,dcol};
    grid[drow][dcol]->attach(td);
    grid[drow][dcol]->notifyObservers();
    grid[drow][dcol]->attach(grid[row][col]);
    dynamic_cast<Enemy*>(grid[drow][dcol])->getPrevious()->attach(td);
    
    availabe.erase(availabe.begin()+q);
    for(auto ob:availabe){
        gene[chamber].push_back(ob);
    }
    
    return dynamic_cast<Dragon*>(grid[drow][dcol]);
}

void Floor::display() { 
    td->print();
    string s = "";
    if(pRace == 'h') s = "Human";
    else if(pRace == 'd') s = "Dwarf"; 
    else if(pRace == 'e') s = "Elves";
    else if(pRace == 'o') s = "Orcs";
    else if(pRace == 'g') s = "God";
    ostringstream ss;
    ss << "Race: " << s << " Gold: " << player->getGold();
    cout << setw(69) << left << ss.str();
    cout << "Floor " << floorNum + 1 << endl;;

    cout << "HP: " << player->getHP() << endl;
    cout << "Atk: " << player->getAtk() << endl;
    cout << "Def: " << player->getDef() << endl;
    cout << "Action: " << action.str() << endl;

    action.str("");
}

void Floor::printTest(){
    for(auto r: graph){
        for(auto c: r){
            cout << c;
        }
        cout << endl;
    }
}

void Floor::setAction(string newAction, GameObject* target) {
// move, collect, see, drink, nextFloor, attackEnemy, killEnemy, attackPlayer, missPlayer, killPlayer
    if(newAction == "move") {
        action << "PC moves " << getTargetDirection(target->getRow(), target->getCol()) << ". ";
    } else if(newAction == "collect") {
        action << "PC collects ";
        if(target->getObjectType() == ObjectType::Treasure) action << target->getObjectType() << " (" << dynamic_cast<Treasure*>(target)->getValue() << " Gold). ";
        else action << target->getObjectType() << ". ";
    } else if(newAction == "see") {
        action << "PC sees ";
        if(target->getObjectType() == ObjectType::Potion) {
            Potion* potion = dynamic_cast<Potion*>(target);
            if(std::find(potionKnown.begin(), potionKnown.end(), potion->getPotionType()) != potionKnown.end()) {
                action << potion->getPotionType() << ". ";
            } else {
                action << "an unknown potion. ";
            }
        } else if(target->getObjectType() == ObjectType::Treasure) {
            action << target->getObjectType() << " (" << dynamic_cast<Treasure*>(target)->getValue() << " Gold). ";
        } else {
            action << target->getObjectType() << ". ";
        }
    } else if(newAction == "drink") {
        action << "PC drinks " << dynamic_cast<Potion*>(target)->getPotionType() << ". ";
        potionKnown.emplace_back(dynamic_cast<Potion*>(target)->getPotionType());
    } else if(newAction == "nextFloor") {
        action << "PC proceeded to the next floor. ";
    } else if(newAction == "attackEnemy") {
        Enemy* enemy = dynamic_cast<Enemy*>(target);
        int damage = std::ceil((100 / (float)(100 + enemy->getDef())) * player->getAtk());
        action << "PC deals " << damage << " damage to " << enemy->getEnemyType() << " (" << enemy->getHP() << " HP). ";
    } else if(newAction == "killEnemy") {
        action << "PC kills " << dynamic_cast<Enemy*>(target)->getEnemyType() << ". ";
    } else if(newAction == "attackPlayer" || newAction == "missPlayer") {
        Enemy* enemy = dynamic_cast<Enemy*>(target);
        
        if(newAction == "attackPlayer") {
            int damage = std::ceil((100 / (float)(100 + player->getDef())) * enemy->getAtk());
            action << enemy->getEnemyType() << " deals " << damage << " damage to PC. ";
        } else {
            action << enemy->getEnemyType() << "'s attack misses PC. ";
        }
        if(enemy->getEnemyType() == EnemyType::Vampire) action << "Vampire uses Blood Steal. ";
        else if(enemy->getEnemyType() == EnemyType::Goblin) action << "Goblin uses Gold Steal. ";
        else if(enemy->getEnemyType() == EnemyType::Troll) action << "Troll uses Health Regeneration. ";
        else if(enemy->getEnemyType() == EnemyType::Dragon) action << "Dragon uses Burn. ";
    } else if(newAction == "killPlayer") {
        action << "PC is killed. ";
    } 
}

bool Floor::getFloorEnd() { return floorEnd; }

bool Floor::getGameEnd() { return gameEnd; }

float Floor::getPlayerScore() { return player->getScore(); }

