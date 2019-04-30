#include "Grid.h"
#include <algorithm>

Grid::Grid(vector<Object*> &sceneObjects) {
    buildGrid(sceneObjects);
}

bool Grid::buildGrid(vector<Object *> &sceneObjects) {

    /*
     * Dimension and Bounding
     */

    Vector lower(99999.f, 99999.f, 99999.f);
    Vector upper(-99999.f, -99999.f, -99999.f);

    for(Object *object : sceneObjects) {
        AABB *box = object->getBoundingBox();

        if(box == nullptr) {
            cout << "Warning: Missing Bounding Box -> Object skipped." << endl;
            continue;
        }

        //Upper
        if(box->getUpper().x > upper.x)
            upper.x = box->getUpper().x;
        if(box->getUpper().y > upper.y)
            upper.y = box->getUpper().y;
        if(box->getUpper().z > upper.z)
            upper.z = box->getUpper().z;

        //Lower
        if(box->getLower().x < lower.x)
            lower.x = box->getLower().x;
        if(box->getLower().y < lower.y)
            lower.y = box->getLower().y;
        if(box->getLower().z < lower.z)
            lower.z = box->getLower().z;

    }

    upper.offsetAllAxis(epsilon);
    lower.offsetAllAxis(-epsilon);

    boundingBox = new AABB(upper, lower);


    /*
     * Spatial Division
     */

    float cellsPerObject = 1.0f;
    float volPerObject = boundingBox->getVolume() / (float) sceneObjects.size();
    float lengthPerObject = cbrt(volPerObject);
    Nx = int(cellsPerObject * boundingBox->getDimension().x / lengthPerObject) + 1;
    Ny = int(cellsPerObject * boundingBox->getDimension().y / lengthPerObject) + 1;
    Nz = int(cellsPerObject * boundingBox->getDimension().z / lengthPerObject) + 1;
    int numCells = Nx * Ny * Nz;
    //cout << "Spatial Division into: " << numCells << " cells: " << Nx << " x " << Ny << " x " << Nz << endl;


    //Init cells
    for (int i = 0; i < numCells; ++i) {
        cellMatrix.push_back(new Cell());
    }


    /*
     * Object Cell Assignment
     */

    for (Object *object : sceneObjects) {
        AABB * box = object->getBoundingBox();
        if(box == nullptr) {
            continue;
        }
        int x_min = std::clamp(int((box->getLower().x - lower.x) * Nx / boundingBox->getDimension().x), 0, Nx - 1); //TODO check formular
        int x_max = std::clamp(int((box->getUpper().x - lower.x) * Nx / boundingBox->getDimension().x), 0, Nx - 1);
        int y_min = std::clamp(int((box->getLower().y - lower.y) * Ny / boundingBox->getDimension().y), 0, Ny - 1); //TODO check formular
        int y_max = std::clamp(int((box->getUpper().y - lower.y) * Ny / boundingBox->getDimension().y), 0, Ny - 1);
        int z_min = std::clamp(int((box->getLower().z - lower.z) * Nz / boundingBox->getDimension().z), 0, Nz - 1); //TODO check formular
        int z_max = std::clamp(int((box->getUpper().z - lower.z) * Nz / boundingBox->getDimension().z), 0, Nz - 1);

        for(int x = x_min; x <= x_max; ++x) {
            for (int y = y_min; y <= y_max; ++y) {
                for (int z = z_min; z <= z_max; ++z) {
                    cellMatrix[x + Nx * y + Nx * Ny * z]->objects.push_back(object);
                }
            }
        }


    }

    return true;
}

AABB *Grid::getBoundingBox() {
    return boundingBox;
}

Cell *Grid::getInitialCell(Ray &ray) {
    //Note that ray has already been intersected with Grid Bounding Box
    Vector enteringPoint = boundingBox->getRecentEnteringPoint();

    /*
     * Compute starting Cell and Indices
     */

    Vector startingPoint = enteringPoint;
    if(ray.t < 0) { //Ray starts inside Grid
        startingPoint = ray.ori;
    }

    ix = std::clamp(int((startingPoint.x - boundingBox->getLower().x) * Nx / boundingBox->getDimension().x), 0, Nx - 1);
    iy = std::clamp(int((startingPoint.y - boundingBox->getLower().y) * Ny / boundingBox->getDimension().y), 0, Ny - 1);
    iz = std::clamp(int((startingPoint.z - boundingBox->getLower().z) * Nz / boundingBox->getDimension().z), 0, Nz - 1);
    Cell *init = cellMatrix[getIndex(ix, iy, iz)];

    /*
     * Set up fields for traversal
     */

    //x
    dtx = (boundingBox->tx_max - boundingBox->tx_min) / Nx;
    if(ray.dir.x > 0.f) {
        tx_next = boundingBox->tx_min + (ix + 1) * dtx;
        ix_step = 1;
        ix_stop = Nx;
    } else {
        tx_next = boundingBox->tx_min + (Nx - ix) * dtx;
        ix_step = -1;
        ix_stop = -1;
    }
    if(ray.dir.x == 0.f) {
        tx_next = 99999.f;
    }

    //y
    dty = (boundingBox->ty_max - boundingBox->ty_min) / Ny;
    if(ray.dir.y > 0.f) {
        ty_next = boundingBox->ty_min + (iy + 1) * dty;
        iy_step = 1;
        iy_stop = Ny;
    } else {
        ty_next = boundingBox->ty_min + (Ny - iy) * dty;
        iy_step = -1;
        iy_stop = -1;
    }
    if(ray.dir.y == 0.f) {
        ty_next = 99999.f;
    }

    //z
    dtz = (boundingBox->tz_max - boundingBox->tz_min) / Nz;
    if(ray.dir.z > 0.f) {
        tz_next = boundingBox->tz_min + (iz + 1) * dtz;
        iz_step = 1;
        iz_stop = Nz;
    } else {
        tz_next = boundingBox->tz_min + (Nz - iz) * dtz;
        iz_step = -1;
        iz_stop = -1;
    }
    if(ray.dir.z == 0.f) {
        tz_next = 99999.f;
    }


    return init;
}

Cell *Grid::getNextCell() {

    /*
     * Traverse in x-direction
     */

    if (tx_next < ty_next && tx_next < tz_next) {
        tx_next += dtx;
        ix += ix_step;
        if(ix == ix_stop) {
            return new Cell(false);
        }
    }
    else if(ty_next < tz_next) { // y-direction
        ty_next += dty;
        iy += iy_step;
        if(iy == iy_stop) {
            return new Cell(false);
        }

    } else { // z-direction
        tz_next += dtz;
        iz += iz_step;
        if(iz == iz_stop) {
            return new Cell(false);
        }
    }

    return cellMatrix[getIndex(ix,iy, iz)];
}

bool Grid::isPointInCurrentCell(Vector point) {
    int x = std::clamp(int((point.x - boundingBox->getLower().x) * Nx / boundingBox->getDimension().x), 0, Nx - 1);
    int y = std::clamp(int((point.y - boundingBox->getLower().y) * Ny / boundingBox->getDimension().y), 0, Ny - 1);
    int z = std::clamp(int((point.z - boundingBox->getLower().z) * Nz / boundingBox->getDimension().z), 0, Nz - 1);

    return ix == x && iy == y && iz == z; //TODO is this 100% correct?
}

int Grid::getIndex(int x, int y, int z) {
    return x + Nx * y + Nx * Ny * z;
}
