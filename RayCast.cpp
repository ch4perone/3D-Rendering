#include "RayCast.h"
#include "VectorMath.cpp"

RayCast::RayCast(Ray ray, Scene *scene) {
    castNewRay(ray, scene);
}

bool RayCast::castNewRay(Ray ray, Scene *scene) {
    float distance = 1000000.f;
    doesIntersect = false;

    //Intersect all object of the scene and store closest one
    for (Object *candidateObject : scene->getObjects()) {
        if (candidateObject->intersect(ray)) {
            if (ray.t < distance && ray.t > 0) {
                doesIntersect = true;
                frontObject=candidateObject;
                distance = ray.t;
            }
        }
    }

    distanceToIntersection = distance;
    ray.t = distance;
    intersectionPoint = vectorAdd(ray.ori, vectorScale(ray.dir, distance));
    return doesIntersect;
}