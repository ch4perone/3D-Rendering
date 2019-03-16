#include "RayCast.h"
#include "VectorMath.cpp"

RayCast::RayCast(Ray ray, Scene *scene) {
    castNewRay(ray, scene);
}

bool RayCast::castNewRay(Ray ray, Scene *scene) {
    //this->ray = Ray(ray.dir, ray.ori);

    float distance = 1000000.f;
    doesIntersect = false;
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
    //this->ray.t = distance;
    intersectionPoint = vectorAdd(ray.ori, vectorScale(ray.dir, distance));
    return doesIntersect;
}

/*Vector RayCast::getIntersectionPoint() {
    return vectorAdd(ray.ori, vectorScale(ray.dir, ray.t));
}*/
