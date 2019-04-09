#ifndef PROJECT_RAYCAST_H
#define PROJECT_RAYCAST_H


#include "defaultStructs.h"
#include "Scene.h"

/**
 * @class Raycast
 * provides an exhaustive ray casting algorithm.
 * Stores results in publicly accessible fields.
 */

class RayCast {
public:
    Object *frontObject;
    bool doesIntersect;
    float distanceToIntersection;
    Vector intersectionPoint;

    RayCast(Ray ray, Scene *scene);
    bool castNewRay(Ray ray, Scene *scene);
    bool intersectObjects(Ray ray, vector<Object*> &objects);
};


#endif //PROJECT_RAYCAST_H
