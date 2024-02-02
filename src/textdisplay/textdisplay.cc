#include "textdisplay.h"
#include "../GameObject/MapComponent/stairs.h"
#include "../GameObject/Character/enemy.h"
#include "../colour.h"
using namespace std;

TextDisplay::TextDisplay(): row{25},col{79}{
    for(int i=0;i<row;++i){
        vector<char> v1;
        for(int j=0;j<col;++j){
            v1.emplace_back(' ');
        }
        theDisplay.emplace_back(v1);
    }
}

void TextDisplay::print() {
    cout << *this;
}

void TextDisplay::clean(){
    for(auto vec: theDisplay){
        for(auto ob: vec){
            ob = ' ';
        }
    }
}

void TextDisplay::notify(Subject &whoFrom){
    int r = whoFrom.getRow();
    int c = whoFrom.getCol();
    if(!(0 <= r && r < 25 && 0 <= c && c < 79)) {
        cerr << "Wrong row or col when changing text display" << endl;
        return; // throw exception
    }
    char s;
    if(whoFrom.getObjectType() == ObjectType::HWall) s = '-';
    else if(whoFrom.getObjectType() == ObjectType::VWall) s = '|';
    else if(whoFrom.getObjectType() == ObjectType::Door) s = '+';
    else if(whoFrom.getObjectType() == ObjectType::Passage) s = '#';
    else if(whoFrom.getObjectType() == ObjectType::Tile) s = '.';
    else if(whoFrom.getObjectType() == ObjectType::Stairs){
        Stairs& stair = static_cast<Stairs&>(whoFrom);
        if(stair.getVisibility()) s = '\\';
        else s = '.';
    }
    else if(whoFrom.getObjectType() == ObjectType::Potion) s = 'P';
    else if(whoFrom.getObjectType() == ObjectType::Weapon) s = 'A';
    else if(whoFrom.getObjectType() == ObjectType::Treasure) s = 'G';
    else if(whoFrom.getObjectType() == ObjectType::Compass) s = 'C';
    else if(whoFrom.getObjectType() == ObjectType::BarrierSuit) s = 'B';
    else if(whoFrom.getObjectType() == ObjectType::Player) s = '@';
    else if(whoFrom.getObjectType() == ObjectType::Enemy){
        Enemy &enemy = static_cast<Enemy&>(whoFrom);
        EnemyType et = enemy.getEnemyType();
        if(et == EnemyType::Werewolf) s = 'W';
        else if(et == EnemyType::Vampire) s = 'V';
        else if(et == EnemyType::Goblin) s = 'N';
        else if(et == EnemyType::Merchant) s = 'M';
        else if(et == EnemyType::Dragon) s = 'D';
        else if(et == EnemyType::Phoenix) s = 'X';
        else if(et == EnemyType::Troll) s = 'T';
        else cerr << "Incorrect enemy type when changing text display" << endl;
    } else cerr << "Incorrect Object type when changing text display" << endl;
    theDisplay[whoFrom.getRow()][whoFrom.getCol()] = s;
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    for(auto vec: td.theDisplay) {
        for(auto c: vec) {
            if(c == '-') out << HWall << c << RESET;
            else if(c == '|') out << VWall << c << RESET;
            else if(c == '+') out << Door << c << RESET;
            else if(c == '#') out << Passage << c << RESET;
            else if(c == '.') out << Tile << c << RESET;
            else if(c == '\\') out << stairs << c << RESET;
            else if(c == 'P') out << Potion << c << RESET;
            else if(c == 'G') out << Treasure << c << RESET;
            else if(c == 'C') out << Compass << c << RESET;
            else if(c == 'B') out << BarrierSuit << c << RESET;
            else if(c == '@') out << Player << c << RESET;
            else if(c == 'W' || c == 'V' || c == 'N' || c == 'M' || c == 'D' || c == 'X' || c == 'T') out << enemy << c << RESET;
            else out << c;
        }
        out << std::endl;
    }
    return out;
}
