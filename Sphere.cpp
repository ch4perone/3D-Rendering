#include "Sphere.h"
#include <iostream>

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

Sphere::Sphere(Vector pos, float radius, Material material) : radius(radius), Object(pos, material) {
    std::cout << "Sphere constructor successful!" << '\n';
};

bool Sphere::intersect(Ray &r) {
      //TODO This is where the magic happens
      // !!! save t in Ray
      // a =
      // b =
      // c =
      // D = b^2 - 4ac
      // if D < 0 {
      //   //complex roots, no intersection
      //    return false;
      // }

// root = t
// maxR not needed? its the threshold for the root.

// bool getLowestRoot(float a, float b, float c, float maxR, float* root) {

    float a = vectorDotProduct(r.dir, r.dir);
    float b = vectorDotProduct(r.dir, (2.0f * (r.ori - pos)));
    float c = vectorDotProduct((r.ori - pos), (r.ori - pos)) - radius*radius;

    // float *root;

    // Check if a solution exists
    float determinant = b*b - 4.0f*a*c;
    // If determinant is negative it means no solutions.
    if (determinant < 0.0f) return false;

    // calculate the two roots: (if determinant == 0 then
    // x1==x2 but let’s disregard that slight optimization)
    float sqrtD = sqrtf(determinant);

    float r1 = (-b - sqrtD) / (2*a);
    float r2 = (-b + sqrtD) / (2*a);
    // Sort so x1 <= x2
    if (r1 > r2) {
      float temp = r2;
      r2 = r1;
      r1 = temp;
    }
    // Get lowest root: && r1 < maxR
    if (r1 > 0) {
      *t = r1;
      return true;
    }
    // It is possible that we want x2 - this can happen
    // if x1 < 0 , ray origin inside sphere
    // && r2 < maxR
    if (r2 > 0) {
      *t = r2;
      return true;
    }

    float distance = sqrtf(a)*t;
    Vector hitpoint = r.ori + t*r.dir;
    Vector normal = (hitpoint - pos) / radius;

    // No (valid) solutions
  //   return false;
  // }

    // double intersectRaySphere(D3DVECTOR rO, D3DVECTOR rV, D3DVECTOR sO, double sR) {
    //    D3DVECTOR Q = sO-rO;
    //    double c = lengthOfVector(Q);
    //    double v = dot(Q,rV);
    //    double d = sR*sR - (c*c - v*v);
    //
    //    // If there was no intersection, return -1
    //    if (d < 0.0) return (-1.0f);
    //
    //    // Return the distance to the [first] intersecting point
    //    return (v - sqrt(d));
    // }



      return false;
}
