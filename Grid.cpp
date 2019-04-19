#include "Grid.h"
#include "VectorMath.cpp"

Grid::Grid(vector<Object*> &sceneObjects) {
    buildGrid(sceneObjects);
}

bool Grid::buildGrid(vector<Object *> &sceneObjects) {

    //TODO build Grid here

    /*
     * Dimension and Bounding
     */

    Vector lower(99999.f, 99999.f, 99999.f);
    Vector upper(-99999.f, -99999.f, -99999.g);

    for(Object *object : sceneObjects) {
        //object->getBoundingBox();
        AABB *box;

        //Upper
        if(box.upper().x > upper.x)
            upper.x = box.x;
        if(box.upper().y > upper.y)
            upper.x = box.y;
        if(box.upper().z > upper.z)
            upper.z = box.z;

        //Lower
        if(box.lower().x < lower.x)
            lower.x = box.x;
        if(box.lower().y > lower.y)
            lower.x = box.y;
        if(box.lower().z > lower.z)
            lower.z = box.z;

    }

    upper = vectorAddToAllAxis(upper, epsilon);
    lower = vectorAddToAllAxis(lower, -epsilon);

    boundingBox = new AABB(upper, lower);

    /*
     * Spatial Division
     */

    float cellsPerObject = 2;
    float objectPerVolume = boundingBox.volume / (float) sceneObjects.size();
    Nx = int(cellsPerObject * boundingBox.size.x / objectPerVolume) + 1;
    Ny = int(cellsPerObject * boundingBox.size.y / objectPerVolume) + 1;
    Nz = int(cellsPerObject * boundingBox.size.z / objectPerVolume) + 1;
    float numCells = Nx * Ny * Nz;

    /*
     * Object Cell Assignment
     */

    for (Object *object : sceneObjects) {
        AABB * box = object->getBoundingBox();
        float x_min = clamp(box.lower().x - lower.x * Nx / boundingBox.size().x, 0, Nx - 1); //TODO check formular
        float x_max = clamp(box.upper().x - lower.x * Nx / boundingBox.size().x, 0, Nx - 1);
        float y_min = clamp(box.lower().y - lower.y * Ny / boundingBox.size().y, 0, Ny - 1); //TODO check formular
        float y_max = clamp(box.upper().y - lower.y * Ny / boundingBox.size().y, 0, Ny - 1);
        float z_min = clamp(box.lower().z - lower.z * Nz / boundingBox.size().z, 0, Nz - 1); //TODO check formular
        float z_max = clamp(box.upper().z - lower.z * Nz / boundingBox.size().z, 0, Nz - 1);

        for(int x = x_min; x <= x_max; ++x) {
            for (int y = y_min; y < y_max; ++y) {
                for (int z = z_min; z < z_max; ++z) {
                    cellMatrix[x][y][z].objects.push_back(object);
                }
            }
        }


    }


    return true;
}

AABB *Grid::getBoundingBox() {
    return boundingBox;
}

Cell Grid::getInitialCell(Ray &ray) {
    //Note that ray has already been intersected with Grid Bounding Box
    Vector enteringPoint = boundingBox->getRecentEnteringPoint();
    Vector exitingPoint = boundingBox->getRecentExitingPoint();

    /*
     * Compute starting Cell and Indices
     */

    Vector startingPoint = enteringPoint;
    if(ray.t < 0) { //Ray starts inside Grid
        startingPoint = ray.ori;
    }

    ix = std::clamp((startingPoint.x - boundingBox.getLower().x) * Nx / boundingBox.size().x, 0, Nx - 1);
    iy = std::clamp((startingPoint.y - boundingBox.getLower().y) * Ny / boundingBox.size().y, 0, Ny - 1);
    iz = std::clamp((startingPoint.z - boundingBox.getLower().z) * Nz / boundingBox.size().z, 0, Nz - 1);

    Cell init = cellMatrix[ix][iy][iz];

    /*
     * Set up fields for traversal
     */

    //x
    dtx = (exitingPoint.x - enteringPoint.x) / Nx;
    if(ray.dir.x > 0.f) {
        tx_next = enteringPoint.x + (ix + 1) * dtx;
        ix_step = 1;
        ix_stop = Nx;
    } else {
        tx_next = enteringPoint.x + (Nx - ix) * dtx;
        ix_step = -1;
        ix_stop = -1;
    }
    if(ray.dir.x == 0.f) {
        tx_next = 99999.f;
    }

    //y
    dty = (exitingPoint.y - enteringPoint.y) / Ny;
    if(ray.dir.y > 0.f) {
        ty_next = enteringPoint.y + (iy + 1) * dty;
        iy_step = 1;
        iy_stop = Ny;
    } else {
        ty_next = enteringPoint.y + (Ny - iy) * dty;
        iy_step = -1;
        iy_stop = -1;
    }
    if(ray.dir.y == 0.f) {
        ty_next = 99999.f;
    }

    //z
    dtz = (exitingPoint.z - enteringPoint.z) / Nz;
    if(ray.dir.z > 0.f) {
        tz_next = enteringPoint.z + (iz + 1) * dtz;
        iz_step = 1;
        iz_stop = Nz;
    } else {
        tz_next = enteringPoint.z + (Nz - iz) * dtz;
        iz_step = -1;
        iz_stop = -1;
    }
    if(ray.dir.z == 0.f) {
        tz_next = 99999.f;
    }

    return init;
}

Cell Grid::getNextCell() {

    /*
     * Traverse in x-direction
     */

    if (tx_next < ty_next && tx_next < tz_next) {
        tx_next += dtx;
        ix += ix_step;
        if(ix == ix_stop) {
            return Cell(false);
        }
    }
    else if(ty_next < tz_next) { // y-direction
        ty_next += dty;
        iy += iy_step;
        if(iy == iy_stop) {
            return Cell(false);
        }

    } else { // z-direction
        tz_next += dtz;
        iz += iz_step;
        if(iz == iz_stop) {
            return Cell(false);
        }
    }

    return cellMatrix[ix][iy][iz];




}

bool Grid::isPointInCurrentCell() {
    //TODO
    return false;
}
