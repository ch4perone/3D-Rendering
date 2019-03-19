#ifndef PROJECT_SPHERE_H
#define PROJECT_SPHERE_H

#include "defaultStructs.h"
#include "Object.h"

class Sphere : public Object {

    float radius;

public:
    Sphere(Vector pos, float radius, Material material);

    bool intersect(Ray &r);

    Vector getNormalInPoint(Vector point) override;

};


#endif //PROJECT_SPHERE_H
