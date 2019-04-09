#include "RayCast.h"
#include "VectorMath.cpp"

RayCast::RayCast(Ray ray, Scene *scene) {
    castNewRay(ray, scene);
}

bool RayCast::castNewRay(Ray ray, Scene *scene) {
    doesIntersect = false;

    /*
     * Grid Intersection
     */

    if (scene->usesGridAcceleration()) {
        Grid *grid = scene->getGrid();

        if(!grid->getBoundingBox()->intersect(ray)) {
            return false;
        }

        while (true) {
            //TODO traverse Grid
            vector<Object*> cellObjects;
            intersectObjects(cellObjects);
            if (doesIntersect) {

            }
        }


        //TODO make sure always to return
    }

    /*
     * else: Naive Intersection
     */

    vector<Object*> sceneObjects = scene->getObjects();
    return intersectObjects(ray, sceneObjects);
}

bool RayCast::intersectObjects(Ray ray, vector<Object*> &objects) {
    float distance = 1000000.f;

    //Intersect all object and store closest one
    for (Object *candidateObject : objects) {
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
