#include "Triangle.h"
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

Triangle::Triangle(Vector pos, Vector pos2, Vector pos3, Material material) : pos2(pos2), pos3(pos3), Object(pos, material) {
  // normal = vectorNormalize( vectorCrossProduct ( vectorSubstract(pos2, pos), vectorSubstract(pos3, pos)));
  // float distance = vectorDotProduct( normal, pos );
};

bool Triangle::intersect(Ray &r) {
      //TODO This is where the magic happens
      // !!! save t in Ray


    Vector e1 = vectorSubstract(pos2, pos);
    Vector e2 = vectorSubstract(pos3, pos);

    Vector pvec = vectorCrossProduct(r.dir, e2);

    float det = vectorDotProduct(pvec, e1);
    float eps = 0.00001f;

    // if (det < eps) return false;

    Vector tvec = vectorSubstract(r.ori, pos);
    // float u = vectorDotProduct(tvec, pvec);
    //
    // if ( u < 0.0f || u > det) return false;

    Vector qvec = vectorCrossProduct(tvec, e1);
    // float v = vectorDotProduct(r.dir,qvec);
    //
    // if (v < 0.0f || v+u > det) return false;

// ELSE
    if (det < eps && det > -eps) return false;

    float invDet = 1.0f /det;
    // Vector tvec = vectorSubstract(r.orig, pos);
    float ui = invDet * vectorDotProduct(tvec,pvec);

    if (ui < 0.0f || ui > 1.0f) return false;

    // CROSS(qvec,tvec,e1);
    // NORMALIZE(qvec);
    float vi = invDet* vectorDotProduct(qvec,r.dir);

    if (vi < 0.0f || ui+vi > 1.0f) return false;


    normal = vectorNormalize(vectorCrossProduct(e1,e2));
    // std::cout << "yes intersect" << endl;
    r.t = - vectorDotProduct(normal,tvec) / vectorDotProduct(r.dir,normal);
    return true;


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
      // return false;
}

Vector Triangle::getNormalInPoint(Vector point) {
    return normal;
}
