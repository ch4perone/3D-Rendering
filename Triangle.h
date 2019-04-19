#ifndef PROJECT_TRIANGLE_H
#define PROJECT_TRIANGLE_H

#include "defaultStructs.h"
#include "Object.h"
#include "AABB.h"

/**
 * @headerfile Triangle
 * inherits from Object class.
 * defines required fields and functions for the Triangle Object.
 * Using Tomas Moeller, Ben Trumbore algorithm with the Cramer's rule
 */

class Triangle : public Object {

    Vector pos2, pos3;
    Vector normal;


public:

    Triangle(Vector pos, Vector pos2, Vector pos3, Material material, bool makeBoundingBox = false);

    bool intersect(Ray &r);

    Vector getNormalInPoint(Vector point) override;

};


#endif //PROJECT_TRIANGLE_H
