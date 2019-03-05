#include "Object.h"
#include <iostream>

// Ray Camera::getPrimaryRay(int x, int y) {
//     return Ray(Vector(1,1,1), Vector(0,0,0));
// }

Material Object::getMaterial() {
      return material;
}

bool Object::intersect(Ray &r) {
      std::cout << "Warning: intersect() of super object called!" << '\n';
      return false;
}

Object::Object(Vector pos, Material material) : pos(pos), material(material) {

}

Object::Object() {

}
