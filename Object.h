#ifndef PROJECT_OBJECT_H
#define PROJECT_OBJECT_H

#include "defaultStructs.h"

class Object {
protected:
    // float size;
    Vector pos;
    Material material;

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

    Material getMaterial();

    Object(Vector pos, Material material);


};


#endif //PROJECT_OBJECT_H
