#ifndef PROJECT_RAYCAST_H
#define PROJECT_RAYCAST_H


#include "defaultStructs.h"
#include "Scene.h"

class RayCast {
public:

    //TODO Ray ray = Ray(Vector(0,0,0), Vector(0,0,0));
    Object *frontObject;
    bool doesIntersect;
    float distanceToIntersection;
    Vector intersectionPoint;

    RayCast(Ray ray, Scene *scene);
    bool castNewRay(Ray ray, Scene *scene);
    //Vector getIntersectionPoint();
};


#endif //PROJECT_RAYCAST_H
