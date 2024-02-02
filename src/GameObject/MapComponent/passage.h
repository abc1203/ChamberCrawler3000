#ifndef PASSAGE_H
#define PASSAGE_H
#include "../mapcomponent.h"

class Passage: public MapComponent {
public:
    Passage(int row, int col);
    ~Passage();
};


#endif
