#ifndef PROJECT_PLANE_H
#define PROJECT_PLANE_H

#include "defaultStructs.h"
#include "Object.h"

/**
 * @headerfile Plane
 * inherits from Object class.
 * defines required fields and functions for the Plane Object.
 */

class Plane : public Object {

    Vector pos2, pos3;
    Vector normal;


public:
    Plane(Vector pos, Vector pos2, Vector pos3, Material material);
    
    bool intersect(Ray &r);
    static bool intersectPlane(Ray &r, Vector normal, Vector position);

    Vector getNormalInPoint(Vector point) override;
};


#endif //PROJECT_PLANE_H
