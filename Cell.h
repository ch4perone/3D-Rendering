#ifndef PROJECT_CELL_H
#define PROJECT_CELL_H


#include "Object.h"

class Cell {
public:
    bool good;
    vector<Object*> objects;
    Cell(bool good = true);
};


#endif //PROJECT_CELL_H
