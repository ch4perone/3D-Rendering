#ifndef PROJECT_AABB_H
#define PROJECT_AABB_H

#include "defaultStructs.h"
#include "Object.h"

class AABB : public Object {

    // pos, pos2, pos3 define the three positions that define the AABB
    Vector pos2;
    Vector normal;
    Vector upper;
    Vector lower;
    Vector enteringPoint;
    Vector exitingPoint;

    // float size;
    // Vector pos;
    // Material material;

    // Vector eye, at, up;
    // float fovy;
    //
    // float near, far;
    // int ResX, ResY;
    //
    // float w,h;
    // Vector xe, ye,ze; //uvn


public:
    // Ray getPrimaryRay(int x, int y);
    bool intersect(Ray &r);
    //
    // Material getMaterial();

    AABB(Vector pos, Vector pos2);
    AABB(Vector pos, Vector pos2, Material material);


    Vector getNormalInPoint(Vector point) override;

    Vector getUpper();
    Vector getLower();

    Vector getRecentEnteringPoint();
    Vector getRecentExitingPoint();
    Vector getDimension();
    float getVolume();

    //Accessible Variables
    float tx_min, ty_min, tz_min;
    float tx_max, ty_max, tz_max;

};


#endif //PROJECT_AABB_H
