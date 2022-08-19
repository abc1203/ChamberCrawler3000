#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
// #include "../floor.h"
#include "../enum.h"
#include "../observer.h"
#include "../subject.h"
// #include "../gameobject.h"

class GameObject;

class TextDisplay: public Observer{
    std::vector<std::vector<char>> theDisplay;
    const int row, col;
 public:
    TextDisplay();
    void notify(Subject &whoFrom) override;
    void clean();
    void print();
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif