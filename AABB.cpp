#include "AABB.h"
#include "VectorMath.cpp"
#include <cmath>


AABB::AABB(Vector pos, Vector pos2) : pos2(pos2), Object(pos, Material()) {
    if (pos.x > pos2.x && pos.y > pos2.y && pos.z > pos2.z) {
        upper = pos;
        lower = pos2;
    }
    else {
        upper = pos2;
        lower = pos;
    }
}

bool AABB::intersect(Ray &r) {
      Vector normalX, normalY, normalZ;

      float a = 1.f / r.dir.x;
      if (a >= 0) {
        tx_min = (lower.x - r.ori.x) * a;
        tx_max = (upper.x - r.ori.x) * a;
        normalX = Vector(-1.f,0.f,0.f);
      }
      else {
        tx_min = (upper.x - r.ori.x) * a;
        tx_max = (lower.x - r.ori.x) * a;
        normalX = Vector(1.f,0.f,0.f);
      }

      float b = 1.f / r.dir.y;
      if (b >= 0) {
        ty_min = (lower.y - r.ori.y) * b;
        ty_max = (upper.y - r.ori.y) * b;
        normalY = Vector(0.f,-1.f,0.f);
      }
      else {
        ty_min = (upper.y - r.ori.y) * b;
        ty_max = (lower.y - r.ori.y) * b;
        normalY = Vector(0.f,1.f,0.f);
      }

      float c = 1.f / r.dir.z;
      if (c >= 0) {
        tz_min = (lower.z - r.ori.z) * c;
        tz_max = (upper.z - r.ori.z) * c;
        normalZ = Vector(0.f,0.f,-1.f);
      }
      else {
        tz_min = (upper.z - r.ori.z) * c;
        tz_max = (lower.z - r.ori.z) * c;
        normalZ = Vector(0.f,0.f,1.f);
      }

      float t0, t1;

      //find largest entering t value = t0
      if (tx_min > ty_min) {
        t0 = tx_min;
        normal = normalX;
      }
      else {
        t0 = ty_min;
        normal = normalY;
      }

      if (tz_min > t0) {
        t0 = tz_min;
        normal = normalZ;
      }
      r.t = t0;
      enteringPoint = vectorAdd(r.ori, vectorScale(r.dir, t0));

      //find smallest exiting t value = t1
      if (tx_max < ty_max) t1 = tx_max;
      else t1 = ty_max;

      if (tz_max < t1) t1 = tz_max;
      exitingPoint = vectorAdd(r.ori, vectorScale(r.dir, t1));


      return (t0 < t1 && t1 > 0.0001f);

}

Vector AABB::getUpper() {
  return upper;
}

Vector AABB::getLower() {
  return lower;
}

Vector AABB::getRecentEnteringPoint() {
  return enteringPoint;
}

Vector AABB::getRecentExitingPoint() {
  return exitingPoint;
}

Vector AABB::getNormalInPoint(Vector point) {
    // normal = Vector(0,0,1);
    //TODO:  fix the bug with the shading of the box (calculating of the normal)
    // std::cout << "normal be like: " << endl;
    // vectorPrint(normal);
    return normal;
}

Vector AABB::getDimension() {
    return vectorSubstract(upper, lower);
}

float AABB::getVolume() {
    Vector dim = getDimension();
    return dim.x * dim.y * dim.z;
}
