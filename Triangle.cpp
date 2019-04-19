#include "Triangle.h"
#include "VectorMath.cpp"
#include <cmath>


Triangle::Triangle(Vector pos, Vector pos2, Vector pos3, Material material, bool makeBoundingBox) : pos2(pos2), pos3(pos3), Object(pos, material) {
    if (makeBoundingBox) {
      float eps = 0.00001f;

      float upperX = std::max(pos.x, std::max(pos2.x, pos3.x)) + eps;
      float upperY = std::max(pos.y, std::max(pos2.y, pos3.y)) + eps;
      float upperZ = std::max(pos.z, std::max(pos2.z, pos3.z)) + eps;
      Vector upper = Vector(upperX,upperY,upperZ);

      float lowerX = std::min(pos.x, std::min(pos2.x, pos3.x)) - eps;
      float lowerY = std::min(pos.y, std::min(pos2.y, pos3.y)) - eps;
      float lowerZ = std::min(pos.z, std::min(pos2.z, pos3.z)) - eps;
      Vector lower = Vector(lowerX,lowerY,lowerZ);

      boundingBox = new AABB(upper,lower);
    }
};

bool Triangle::intersect(Ray &r) {

    float eps = 0.00001f;
    Vector e1 = vectorSubstract(pos2, pos); // = b - a
    Vector e2 = vectorSubstract(pos3, pos); // = c - a

    Vector pvec = vectorCrossProduct(r.dir, e2); // = d x (c-a)
    Vector tvec = vectorSubstract(r.ori, pos); // = o - a
    Vector qvec = vectorCrossProduct(tvec, e1); // = (o-a) x (b-a)

    float det = vectorDotProduct(pvec, e1); // = d x ( c-a) . (b-a) = det of first vector

    if (det < eps && det > -eps) return false; // det can not be < 0

    float invDet = 1.0f /det; // D^-1

    float beta = invDet * vectorDotProduct(tvec,pvec); // D^-1 .(o-a) . (d x (c-a))
    if (beta < 0.0f || beta > 1.0f) return false; // beta has to be between 0 and 1

    float gamma = invDet* vectorDotProduct(qvec,r.dir); // D^-1 . d ((o-a) x (b-a))
    if (gamma < 0.0f || beta+gamma > 1.0f) return false;


    normal = vectorNormalize(vectorCrossProduct(e1,e2));
    r.t = - vectorDotProduct(normal,tvec) / vectorDotProduct(r.dir,normal);

    return true;

}

Vector Triangle::getNormalInPoint(Vector point) {
    return normal;
}
