#include "Grid.h"

Grid::Grid(vector<Object*> &sceneObjects) {
    buildGrid(sceneObjects);
}

bool Grid::buildGrid(vector<Object *> &sceneObjects) {

    //TODO build Grid here



    return true;
}

AABB *Grid::getBoundingBox() {
    return boundingBox;
}
