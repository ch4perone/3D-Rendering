#ifndef PROJECT_PLANE_H
#define PROJECT_PLANE_H

#include "defaultStructs.h"
#include "Object.h"

class Plane : public Object {

    // pos, pos2, pos3 define the three positions that define the plane
    Vector pos2, pos3;
    Vector normal;

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
    static bool intersectPlane(Ray &r, Vector normal, Vector position);
    //
    // Material getMaterial();

    Plane(Vector pos, Vector pos2, Vector pos3, Material material);

    Vector getNormalInPoint(Vector point) override;



};


#endif //PROJECT_PLANE_H
