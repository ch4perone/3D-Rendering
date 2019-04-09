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
      else {
        tx_min = (x1 - ox) * a;
        tx_max = (x0 - ox) * a;
      }

      float b = 1.f / dy;
      if (b >= 0) {
        ty_min = (y0 - oy) * b;
        ty_max = (y1 - oy) * b;
      }
      else {
        ty_min = (y1 - oy) * b;
        ty_max = (y0 - oy) * b;
      }

      float c = 1.f / dz;
      if (c >= 0) {
        tz_min = (z0 - oz) * c;
        tz_max = (z1 - oz) * c;
      }
      else {
        tz_min = (z1 - oz) * c;
        tz_max = (z0 - oz) * c;
      }

      float t0, t1;

      //find largest entering t value
      if (tx_min > ty_min) t0 = tx_min;
      else t0 = ty_min;

      if (tz_min > t0) t0 = tz_min;

      //find smallest exiting t value
      if (tx_max < ty_max) t1 = tx_max;
      else t1 = ty_max;

      if (tz_max < t1) t1 = tz_max;

      return (t0 < t1 && t1 > kEpsilon);


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
