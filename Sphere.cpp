#include "Sphere.h"
#include "Vector.h"
#include <iostream>
#include <cmath>

Sphere::Sphere(Vector pos, float radius, Material material, bool makeBoundingBox) : radius(radius), Object(pos, material) {
    if (makeBoundingBox) {
      // float eps = 0.00001f;

      float upperX = pos.x + radius + epsilon;
      float upperY = pos.y + radius + epsilon;
      float upperZ = pos.z + radius + epsilon;
      Vector upper = Vector(upperX,upperY,upperZ);

      float lowerX = pos.x - radius - epsilon;
      float lowerY = pos.y - radius - epsilon;
      float lowerZ = pos.z - radius - epsilon;
      Vector lower = Vector(lowerX,lowerY,lowerZ);

      boundingBox = new AABB(upper,lower);
    }
};

bool Sphere::intersect(Ray &r) {

    float a = r.dir.dot_product(r.dir);
    float b = r.dir.dot_product((r.ori - pos) * 2.f);
    float c = ((r.ori - pos).dot_product(r.ori - pos)) - radius*radius;

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
