#include "Plane.h"
#include "VectorMath.cpp"
#include <cmath>



// Ray Camera::getPrimaryRay(int x, int y) {
//     return Ray(Vector(1,1,1), Vector(0,0,0));
// }

// Material Object::getMaterial() {
//       return material;
// }
//
// bool Object::intersect(Ray &r) {
//       std::cout << "Warning: intersect of super object called!" << '\n';
//       return false;
// }
//
// Object::Object(){
//
// }

Plane::Plane(Vector pos, Vector pos2, Vector pos3, Material material) : pos2(pos2), pos3(pos3), Object(pos, material) {
  normal = vectorNormalize( vectorCrossProduct ( vectorSubstract(pos2, pos), vectorSubstract(pos3, pos)));
  // float distance = vectorDotProduct( normal, pos );
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
