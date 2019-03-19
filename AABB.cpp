#include "AABB.h"
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

AABB::AABB(Vector pos, Vector pos2, Material material) : pos2(pos2), Object(pos, material) {
  // normal = vectorNormalize( vectorCrossProduct ( vectorSubstract(pos2, pos), vectorSubstract(pos3, pos)));
  // float distance = vectorDotProduct( normal, pos );
  // TODO: define normal;
};

bool AABB::intersect(Ray &r) {
      //TODO This is where the magic happens
      // !!! save t in Ray

      // have to define these planes:
      float x0, x1;

      float ox = r.ori.x;
      float oy = r.ori.y;
      float oz = r.ori.z;

      float dx = r.dir.x;
      float dy = r.dir.y;
      float dz = r.dir.z;

      float tx_min, ty_min, tz_min;
      float tx_max, ty_max, tz_min;

      float a = 1.f / dx;
      if (a >= 0) {
        tx_min = (x0 - ox) * a;
        tx_max = (x1 - ox) * a;
      }


      // float denom = vectorDotProduct(normal, r.dir);
      //
      // if (fabs(denom) > 0.0001f) {
      //     float t = vectorDotProduct(vectorSubstract(pos, r.ori), normal) / denom;
      //
      //     if (t >= 0) {
      //       r.t = t;
      //       return true;
      //     }
      // }
      return false;
}

Vector AABB::getNormalInPoint(Vector point) {
    return normal;
}
