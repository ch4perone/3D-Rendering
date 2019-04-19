#ifndef PROJECT_CYLINDER_H
#define PROJECT_CYLINDER_H

#include "defaultStructs.h"
#include "Object.h"
#include "AABB.h"


/**
 * @headerfile Cylinder
 * inherits from Object class.
 * defines required fields and functions for the Cylinder Object.
 * There are three kinds of intersection, with the laternal surface and the two disks,
 * we go through these cases to find the cloasest intersection.
 */

class Cylinder : public Object {

    enum INTERSECTION_TYPE {
      DISK1 = 0,
      DISK2,
      CYLINDER,
      INT_TYPE_END
    };

    Vector pos2;
    float radius;
    float radius2;
    float height;
    Vector intersection;
    Vector projection;
    Vector diskNormal;

    INTERSECTION_TYPE latestValidIntersection;


public:
    Cylinder(Vector pos, float radius, Vector pos2, float radius2, Material material, bool makeBoundingBox = false);

    bool intersect(Ray &r);

    Vector getNormalInPoint(Vector point) override;

//private:
    // bool intersectDisk(Ray &ray, INTERSECTION_TYPE disk);
};


#endif //PROJECT_CYLINDER_H
