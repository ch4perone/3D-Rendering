#include "Sphere.h"
#include "VectorMath.cpp"
#include <iostream>
#include <cmath>

Sphere::Sphere(Vector pos, float radius, Material material, bool makeBoundingBox) : radius(radius), Object(pos, material) {
    if (makeBoundingBox) {
      float eps = 0.00001f;

      float upperX = pos.x + radius + eps;
      float upperY = pos.y + radius + eps;
      float upperZ = pos.z + radius + eps;
      Vector upper(upperX, upperY, upperZ);

      float lowerX = pos.x - radius - eps;
      float lowerY = pos.y - radius - eps;
      float lowerZ = pos.z - radius - eps;
      Vector lower(lowerX,lowerY,lowerZ);

      boundingBox = new AABB(upper, lower);
    }
};

bool Sphere::intersect(Ray &r) {

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
    return normal;
}
