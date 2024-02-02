#ifndef TILE_H
#define TILE_H
#include "../mapcomponent.h"

class Tile: public MapComponent {
public:
    Tile(int row, int col);
    ~Tile();
};


#endif
