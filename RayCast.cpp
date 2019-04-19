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

        if(true) { //
            //TODO starts inside grid
        }

        if(!grid->getBoundingBox()->intersect(ray)) {
            return false;
        }
        grid->getInitialCell(ray);

        /*
         * Traverse Grid
         */
        //TODO get first cell
        while (true) { //TODO while inside grid (getNextCell)

            vector<Object*> cellObjects;
            intersectObjects(ray, cellObjects);
            if (doesIntersect) {
                //TODO check that intersection is inside cell
                return true;
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
