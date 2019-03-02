#ifndef PROJECT_SPHERE_H
#define PROJECT_SPHERE_H

#include "defaultStructs.h"
#include "Object.h"

class Sphere : public Object {

    float radius;
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
    // Ray PrimaryRay(int x, int y);
    bool intersect(Ray &r);
    //
    // Material getMaterial();

    Sphere(Vector pos, float radius, Material material);


};


#endif //PROJECT_SPHERE_H
