#include "Plane.h"
#include "Vector.h"
#include <cmath>


Plane::Plane(Vector pos, Vector pos2, Vector pos3, Material material) : pos2(pos2), pos3(pos3), Object(pos, material) {
  normal = (pos2 - pos).cross_product(pos3 - pos).normalize();
}

bool Plane::intersectPlane(Ray &r, Vector normal, Vector position){
    float denom = normal.dot_product(r.dir);

    if (fabs(denom) > 0.0001f) {
        float t = (position - r.ori).dot_product(normal) / denom;

        if (t >= 0) {
          r.t = t;
          return true;
        }
    }
    return false;
}

bool Plane::intersect(Ray &r) {
      float denom = normal.dot_product(r.dir);

      if (fabs(denom) > 0.0001f) {
          float t = (pos - r.ori).dot_product(normal) / denom;

          if (t >= 0) {
            r.t = t;
            return true;
          }
      }
      return false;
}

Vector Plane::getNormalInPoint(Vector point) {
    return normal;
}
