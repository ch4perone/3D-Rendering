#ifndef PROJECT_OBJECT_H
#define PROJECT_OBJECT_H

#include "defaultStructs.h"
#include <vector>

using namespace std;

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

    Object();
    Object(Vector pos, Material material);
    virtual bool intersect(Ray &r);
    Color computeShading(Vector intersectionPoint, Vector eyePosition, vector<Light> &activeLightSources);

    //getter
    Material getMaterial();
    virtual Vector getNormalInPoint(Vector point);
    Vector getReflectionInPoint(Vector point, Vector eyePosition, bool interior);

    bool isReflective();
    bool isTranslucid();
};


#endif //PROJECT_OBJECT_H
