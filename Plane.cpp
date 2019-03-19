#include "Plane.h"
#include "VectorMath.cpp"
#include <cmath>


Plane::Plane(Vector pos, Vector pos2, Vector pos3, Material material) : pos2(pos2), pos3(pos3), Object(pos, material) {
  normal = vectorNormalize( vectorCrossProduct ( vectorSubstract(pos2, pos), vectorSubstract(pos3, pos)));
};

bool Plane::intersectPlane(Ray &r, Vector normal, Vector position){
    float denom = vectorDotProduct(normal, r.dir);

    if (fabs(denom) > 0.0001f) {
        float t = vectorDotProduct(vectorSubstract(position, r.ori), normal) / denom;

        if (t >= 0) {
          r.t = t;
          return true;
        }
    }
    return false;
}

bool Plane::intersect(Ray &r) {
      float denom = vectorDotProduct(normal, r.dir);

      if (fabs(denom) > 0.0001f) {
          float t = vectorDotProduct(vectorSubstract(pos, r.ori), normal) / denom;

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
