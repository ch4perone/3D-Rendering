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
      // b =
      // a =
      // c =
      // D = b^2 - 4ac
      // if D < 0 {
      //   //complex roots, no intersection
      // }

    return false;
}
