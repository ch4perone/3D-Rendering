#include "Cylinder.h"
#include "Vector.h"
#include "Plane.h"
#include <iostream>
#include <cmath>


Cylinder::Cylinder(Vector pos, float radius, Vector pos2, float radius2, Material material, bool makeBoundingBox) : radius(radius), pos2(pos2), radius2(radius2), Object(pos, material) {
    height = pos.distance(pos2);
    if (makeBoundingBox) {
      // float eps = 0.00001f;

      //TODO: make this happen

      // float upperX = pos.x + radius + eps;
      // float upperY = pos.y + radius + eps;
      // float upperZ = pos.z + radius + eps;
      // Vector upper = Vector(upperX,upperY,upperZ);
      //
      // float lowerX = pos.x - radius - eps;
      // float lowerY = pos.y - radius - eps;
      // float lowerZ = pos.z - radius - eps;
      // Vector lower = Vector(lowerX,lowerY,lowerZ);
      //
      // boundingBox = new AABB(upper,lower);
    }
};

bool Cylinder::intersect(Ray &r) {
    float intersectionDistances[3] = {-1.f, -1.f, -1.f};
    // Check it is a cylinder and not a cone
    if (radius != radius2) {
      std::cout << "Radii of cylinder bases are different, might be a cone." << endl;
      std::cout << radius << endl;
      std::cout << radius2 << endl;
    }

    float cxmin, cymin, czmin, cxmax, cymax, czmax;

    //use epsilon because of computation errors between floats
    float eps = 0.00001;
    float rad_sq = radius * radius;

    /* Check if the ray intersects with the first disk
    (using the plane intersection,
    followed by checking the distance form the center) */
    Vector n = pos.directionTo(pos2).normalize();
    if (Plane::intersectPlane(r,n,pos2)){
      Vector p = r.ori + (r.dir * r.t);
      Vector v = p - pos2;
      float d2 = v.dot_product(v);
      if (d2 <= rad_sq) {
        intersectionDistances[DISK1] = r.t;
      }
    }

    // Check if the ray intersects with the second disk
    n = pos2.directionTo(pos).normalize();
    if (Plane::intersectPlane(r,n,pos)){
      Vector p = r.ori + (r.dir * r.t);
      Vector v = p - pos;
      float d2 = v.dot_product(v);
      if (d2 <= rad_sq) {
        intersectionDistances[DISK2] = r.t;
      }
    }

    // setting czmin and czmax
    if (pos.z < pos2.z) { czmin = pos.z - radius; czmax = pos2.z + radius; } else { czmin = pos2.z - radius; czmax = pos.z + radius; }
    if (pos.y < pos2.y) { cymin = pos.y - radius; cymax = pos2.y + radius; } else { cymin = pos2.y - radius; cymax = pos.y + radius; }
    if (pos.x < pos2.x) { cxmin = pos.x - radius; cxmax = pos2.x + radius; } else { cxmin = pos2.x - radius; cxmax = pos.x + radius; }

    // if (r.ori.z >= czmax && (r.ori.z + r.dir.z) > czmax) return false;
    // if (r.ori.z <= czmin && (r.ori.z + r.dir.z) < czmin) return false;
    // if (r.ori.y >= cymax && (r.ori.y + r.dir.y) > cymax) return false;
    // if (r.ori.y <= cymin && (r.ori.y + r.dir.y) < cymin) return false;
    // if (r.ori.x >= cxmax && (r.ori.x + r.dir.x) > cxmax) return false;
    // if (r.ori.x <= cxmin && (r.ori.x + r.dir.x) < cxmin) return false;


    Vector AB = pos2 - pos;
    Vector AO = r.ori - pos;
    Vector AOxAB = AO % AB;
    Vector VxAB  = r.dir % AB;
    float ab2 = AB.dot_product(AB);

    float a = VxAB.dot_product(VxAB);
    float b = 2 * (VxAB.dot_product(AOxAB));
    float c = (AOxAB.dot_product(AOxAB)) - (radius*radius * ab2);
    float d = b * b - 4 * a * c;

    if (d > 0) {
      float t2 = (-b - sqrtf(d)) / (2 * a);
      if (t2 > 0) {
        // intersection point
        intersection = r.ori + (r.dir * t2);
        // intersection projected onto cylinder axis
        projection = pos + ((AB * (AB.dot_product(intersection - pos))) / ab2);
        // if ((projection - pos).length() + (pos2 - projection).length() > AB.length()) return; /// THIS IS THE SLOW SAFE WAY
        if (!(projection.z > czmax - radius + eps || projection.z < czmin + radius - eps ||
        projection.y > cymax - radius + eps || projection.y < cymin + radius - eps ||
        projection.x > cxmax - radius + eps || projection.x < cxmin + radius - eps )) {

          // normal = (intersection - projection);
          // normal.normalise();
          r.t = t2;
          intersectionDistances[CYLINDER] = r.t;
        }
      }
    }

    INTERSECTION_TYPE closestINTERSECT;
    float distance = 10000.f;

    for (int type = 0; type < INT_TYPE_END; ++type) {
      if(intersectionDistances[type] < distance && intersectionDistances[type] > 0) {
        closestINTERSECT = (INTERSECTION_TYPE) type;
        distance = intersectionDistances[type];
      }
    }

    if(distance > 0 && distance != 10000.f) {
      latestValidIntersection = closestINTERSECT;
      r.t = distance;
      return true;
    }

    return false;
}


// Calculate the normal in a point on the surface
// it is a vertical vector in the bases and a vector
// having the direction of the vector from the axis to the point
Vector Cylinder::getNormalInPoint(Vector point) {
    Vector normal;

    // Calculate the normal depending on which part of the cylinder the ray intersects with
    if(latestValidIntersection == CYLINDER) {
      normal = (point - projection).normalize();
    }
    if(latestValidIntersection == DISK1) {
      normal = (point - pos).normalize();
    }
    if(latestValidIntersection == DISK2) {
      normal = (point - pos2).normalize();
    }
    return normal;
}
