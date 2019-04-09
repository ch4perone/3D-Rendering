#ifndef PROJECT_GRID_H
#define PROJECT_GRID_H

#include <vector>
#include "Cell.h"
#include "AABB.h"

using namespace std;

typedef vector<vector<vector<Cell>>> Matrix3D;

class Grid {

    AABB* boundingBox;
public:

    Grid(vector<Object*> &sceneObjects);
    Matrix3D cellMatrix;

    //Getter
    AABB* getBoundingBox();
private:
    bool buildGrid(vector<Object*> &sceneObjects); //TODO implement
};


#endif //PROJECT_GRID_H
