#ifndef PROJECT_OBJECT_H
#define PROJECT_OBJECT_H

#include "defaultStructs.h"
#include <vector>

using namespace std;

/**
 * @class Object
 * defines required fields and functions for all scene objects.
 * Super class, will only be used abstractly.
 * Virtual function are overwritten in sub-classes.
 *
 */

class Object {
protected:
    Vector pos;
    Material material;

public:

    Object();
    Object(Vector pos, Material material);
    virtual bool intersect(Ray &r);
    Color computeShading(Vector intersectionPoint, Vector eyePosition, vector<Light> &activeLightSources);

    //getter
    Material getMaterial();
    virtual Vector getNormalInPoint(Vector point);
    Vector getReflectionInPoint(Vector point, Vector eyePosition, bool interior);
    Vector getRefractionDirectionInPoint(Vector point, Vector eyePosition, float indexOfRefraction, bool interior);


    bool isReflective();
    bool isTranslucid();
};


#endif //PROJECT_OBJECT_H
