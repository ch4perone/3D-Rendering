#include "Triangle.h"
#include "Vector.h"
#include <cmath>


Triangle::Triangle(Vector pos, Vector pos2, Vector pos3, Material material, bool makeBoundingBox) : pos2(pos2), pos3(pos3), Object(pos, material) {
    if (makeBoundingBox) {
      // float eps = 0.00001f;

      float upperX = std::max(pos.x, std::max(pos2.x, pos3.x)) + epsilon;
      float upperY = std::max(pos.y, std::max(pos2.y, pos3.y)) + epsilon;
      float upperZ = std::max(pos.z, std::max(pos2.z, pos3.z)) + epsilon;
      Vector upper = Vector(upperX,upperY,upperZ);

      float lowerX = std::min(pos.x, std::min(pos2.x, pos3.x)) - epsilon;
      float lowerY = std::min(pos.y, std::min(pos2.y, pos3.y)) - epsilon;
      float lowerZ = std::min(pos.z, std::min(pos2.z, pos3.z)) - epsilon;
      Vector lower = Vector(lowerX,lowerY,lowerZ);

      boundingBox = new AABB(upper,lower);
    }
};

bool Triangle::intersect(Ray &r) {

    if(rayInMailbox(r)) {
        return true;
    }
    // float eps = 0.00001f;
    Vector e1 = pos2 - pos; // = b - a
    Vector e2 = pos3 - pos; // = c - a

    Vector pvec = r.dir % e2; // = d x (c-a)
    Vector tvec = r.ori - pos; // = o - a
    Vector qvec = tvec % e1; // = (o-a) x (b-a)

    float det = pvec.dot_product(e1); // = d x ( c-a) . (b-a) = det of first vector

    if (det < epsilon && det > -epsilon) return false; // det can not be < 0

    float invDet = 1.0f /det; // D^-1

    float beta = invDet * (tvec.dot_product(pvec)); // D^-1 .(o-a) . (d x (c-a))
    if (beta < 0.0f || beta > 1.0f) return false; // beta has to be between 0 and 1

    float gamma = invDet* (qvec.dot_product(r.dir)); // D^-1 . d ((o-a) x (b-a))
    if (gamma < 0.0f || beta+gamma > 1.0f) return false;


    normal = (e1 % e2).normalize();
    r.t = - (normal.dot_product(tvec)) / (r.dir.dot_product(normal));

    recentRayId = r.id;
    recentRayDistance = r.t;

    return true;

}

Vector Triangle::getNormalInPoint(Vector point) {
    return normal;
}
