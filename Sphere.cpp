#include "Sphere.h"
#include "VectorMath.cpp"
#include <iostream>
#include <cmath>

Sphere::Sphere(Vector pos, float radius, Material material) : radius(radius), Object(pos, material) {
};

bool Sphere::intersect(Ray &r) {

    // Vector doc = vectorSubstract(pos, r.ori);
    // float doc_sq = vectorDotProduct(doc,doc);
    //
    // float b = vectorDotProduct(r.dir,doc);
    // float r_sq = radius*radius;
    //
    // if (doc_sq > r_sq) {
    //   if (b<0) return false;
    //
    //   float R = b*b - doc_sq + r_sq;
    //   if (R<0) return false;
    //
    //   float t1 = b- sqrtf(R);
    //   r.t = t1;
    //   return true;
    // }
    //
    // float R = b*b - doc_sq + r_sq;
    // float t1 = b- sqrtf(R);
    // float t2 = b+ sqrtf(R);
    //
    // if (t1 > t2) {
    //   float temp = t2;
    //   t2 = t1;
    //   t1 = temp;
    // }
    // // Get lowest root: && r1 < maxR
    // if (t1 > 0) {
    //   r.t = t1;
    //   return true;
    // }
    // // It is possible that we want x2 - this can happen
    // // if x1 < 0 , ray origin inside sphere
    // // && r2 < maxR
    // if (t2 > 0) {
    //   r.t = t2;
    //   return true;
    // }


  // Correct thing without optimization:

    float a = vectorDotProduct(r.dir, r.dir);
    float b = vectorDotProduct(r.dir, vectorScale((vectorSubstract(r.ori, pos)), 2.f));
    float c = vectorDotProduct(vectorSubstract(r.ori, pos), vectorSubstract(r.ori, pos)) - radius*radius;

    // Check if a solution exists
    float discriminant = b*b - 4.0f*a*c;
    // If discriminant is negative it means no solutions = no intersections.
    if (discriminant < 0.0f) return false;

    // calculate the two roots: (if discriminant == 0 then
    // x1==x2 but let’s disregard that slight optimization)
    float sqrtD = sqrtf(discriminant);

    float r1 = (-b - sqrtD) / (2*a);
    float r2 = (-b + sqrtD) / (2*a);
    // Sort so x1 <= x2
    if (r1 > r2) {
      float temp = r2;
      r2 = r1;
      r1 = temp;
    }
    // Get lowest root:
    if (r1 > 0) {
      r.t = r1;
      return true;
    }
    // It is possible that we want x2 - this can happen
    // if x1 < 0 , ray origin inside sphere
    if (r2 > 0) {
      r.t = r2;
      return true;
    }

    return false;
}

Vector Sphere::getNormalInPoint(Vector point) {
    Vector normal = Vector((point.x - pos.x) / radius, (point.y - pos.y) / radius, (point.z - pos.z) / radius);
    return normal; //TODO is this normalized already. I think so
}
