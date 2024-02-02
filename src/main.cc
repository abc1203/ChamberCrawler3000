#include <iostream>
#include <string>
#include "game.h"
using namespace std;


int main(int argc, char *argv[]) {
    string inputFile = "defaultMap.txt";
    bool givenMap = false;
    if(argc > 1){
        inputFile = argv[1];
        givenMap = true;
    }
    
    Game g(inputFile, givenMap);

    g.play();
    // Floor f;
    // f.printTest();
}
