#ifndef PROJECT_GRID_H
#define PROJECT_GRID_H

#include <vector>
#include "Cell.h"
#include "AABB.h"

using namespace std;

typedef vector<vector<vector<Cell>>> Matrix3D;

class Grid {

    AABB* boundingBox = nullptr;

    int Nx, Ny, Nz;
    float dtx, dty, dtz;
    float tx_next, ty_next, tz_next;
    int ix, iy, iz;
    int ix_step, iy_step, iz_step;
    int ix_stop, iy_stop, iz_stop;

public:

    Grid(vector<Object*> &sceneObjects);
    Matrix3D cellMatrix;

    //Getter
    AABB* getBoundingBox();
    Cell getInitialCell(Ray &ray);
    Cell getNextCell();

    bool isPointInCurrentCell(Vector point);

private:
    bool buildGrid(vector<Object*> &sceneObjects); //TODO implement
};


#endif //PROJECT_GRID_H
