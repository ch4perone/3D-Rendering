#ifndef PROJECT_CYLINDER_H
#define PROJECT_CYLINDER_H

#include "defaultStructs.h"
#include "Object.h"

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
    Cylinder(Vector pos, float radius, Vector pos2, float radius2, Material material);

    bool intersect(Ray &r);

    Vector getNormalInPoint(Vector point) override;

//private:
    // bool intersectDisk(Ray &ray, INTERSECTION_TYPE disk);

    // bool intersect_base(Ray &r, const Vector& c, float& t);

};


#endif //PROJECT_CYLINDER_H
