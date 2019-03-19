#include "Cylinder.h"
#include "VectorMath.cpp"
#include "Plane.h"
#include <iostream>
#include <cmath>


Cylinder::Cylinder(Vector pos, float radius, Vector pos2, float radius2, Material material) : radius(radius), pos2(pos2), radius2(radius2), Object(pos, material) {
    height = vectorDistance(pos, pos2);
};

bool Cylinder::intersect(Ray &r) {

    float intersectionDistances[3] = {-1.f, -1.f, -1.f};
    // Check it is a cylinder and not a cone
    if (radius != radius2) {
      std::cout << "radii of cylinder bases are different, might be a cone." << endl;
      std::cout << radius << endl;
      std::cout << radius2 << endl;
    }


    float cxmin, cymin, czmin, cxmax, cymax, czmax;

    //use epsilon because of computation errors between floats
    float eps = 0.00001;
    // float t2 = -1;
    float rad2 = radius * radius;

    Vector n = vectorNormalize(vectorDirection(pos, pos2));
    if (Plane::intersectPlane(r,n,pos2)){
      // float t = 0;
      Vector p = vectorAdd(r.ori,vectorScale(r.dir,r.t));
      Vector v = vectorSubstract(p,pos2);
      float d2 = vectorDotProduct(v,v);
      // std::cout << "in disk 1" << endl;
      // float rad2 = radius * radius;
      if (d2 <= rad2) {
        intersectionDistances[DISK1] = r.t;
        // std::cout << "disk 1 intersection" << intersectionDistances[DISK1] << endl;
      }
    }

    n = vectorNormalize(vectorDirection(pos2, pos));
    if (Plane::intersectPlane(r,n,pos)){
      // float t = 0;
      Vector p = vectorAdd(r.ori,(vectorScale(r.dir,r.t)));
      Vector v = vectorSubstract(p,pos);
      float d2 = vectorDotProduct(v,v);
      // float rad2 = radius * radius;
      // return (d2 <= rad2);
      // std::cout << "in disk 2" << endl;
      if (d2 <= rad2) {
        intersectionDistances[DISK2] = r.t;
        // std::cout << "disk 2 intersection" << intersectionDistances[DISK2] << endl;
      }
    }

    if (pos.z < pos2.z) { czmin = pos.z - radius; czmax = pos2.z + radius; } else { czmin = pos2.z - radius; czmax = pos.z + radius; }
    if (pos.y < pos2.y) { cymin = pos.y - radius; cymax = pos2.y + radius; } else { cymin = pos2.y - radius; cymax = pos.y + radius; }
    if (pos.x < pos2.x) { cxmin = pos.x - radius; cxmax = pos2.x + radius; } else { cxmin = pos2.x - radius; cxmax = pos.x + radius; }

    // if (r.ori.z >= czmax && (r.ori.z + r.dir.z) > czmax) return false;
    // if (r.ori.z <= czmin && (r.ori.z + r.dir.z) < czmin) return false;
    // if (r.ori.y >= cymax && (r.ori.y + r.dir.y) > cymax) return false;
    // if (r.ori.y <= cymin && (r.ori.y + r.dir.y) < cymin) return false;
    // if (r.ori.x >= cxmax && (r.ori.x + r.dir.x) > cxmax) return false;
    // if (r.ori.x <= cxmin && (r.ori.x + r.dir.x) < cxmin) return false;


    Vector AB = vectorSubstract(pos2,pos);
    Vector AO = vectorSubstract(r.ori,pos);
    Vector AOxAB = vectorCrossProduct(AO,AB);
    Vector VxAB  = vectorCrossProduct(r.dir,AB);
    float ab2 = vectorDotProduct(AB,AB);
    float a = vectorDotProduct(VxAB,VxAB);
    float b = 2 * vectorDotProduct(VxAB,AOxAB);
    float c = vectorDotProduct(AOxAB,AOxAB) - (radius*radius * ab2);
    float d = b * b - 4 * a * c;
    if (d > 0) {
      float t2 = (-b - sqrtf(d)) / (2 * a);
      if (t2 > 0) {
        intersection = vectorAdd(r.ori,vectorScale(r.dir,t2));        /// intersection point
        projection = vectorAdd(pos,(vectorScale(AB,(vectorDotProduct(AB,(vectorSubstract(intersection,pos))) / ab2)))); /// intersection projected onto cylinder axis
        // if ((projection - pos).length() + (pos2 - projection).length() > AB.length()) return; /// THIS IS THE SLOW SAFE WAY
        if (!(projection.z > czmax - radius + eps || projection.z < czmin + radius - eps ||
        projection.y > cymax - radius + eps || projection.y < cymin + radius - eps ||
        projection.x > cxmax - radius + eps || projection.x < cxmin + radius - eps )) {
          // return false; /// THIS IS THE FASTER BUGGY WAY

          // normal = (intersection - projection);
          // normal.normalise();
          // std::cout << "cyl intersection: " << t2 << '\n';
          r.t = t2;
          intersectionDistances[CYLINDER] = r.t;
        }
      }
    }

    // std::cout << "intersect cyl" << endl;

    INTERSECTION_TYPE closestINTERSECT;
    float distance = 10000.f;
    // intersectionDistances[CYLINDER] = 0;

    for (int type = 0; type < INT_TYPE_END; ++type) {
      // std::cout << "intersectionDistances[type]: " << intersectionDistances[type] << endl;
      if(intersectionDistances[type] < distance && intersectionDistances[type] > 0) {
        closestINTERSECT = (INTERSECTION_TYPE) type;
        distance = intersectionDistances[type];
      }
    }

    if(distance > 0 && distance != 10000.f) {
      latestValidIntersection = closestINTERSECT;
      r.t = distance;
      // std::cout << "intersects at: " << distance << endl;
      return true;
    }


    return false;
}

    // bool d3RayCylinderIntersection(const DCylinder &cylinder,const DVector3 &org,const DVector3 &dir,float &lambda,DVector3 &normal,DVector3 &newPosition)
    // // Ray and cylinder intersection
    // // If hit, returns true and the intersection point in 'newPosition' with a normal and distance along
    // // the ray ('lambda')
    // {
    //   DVector3 RC;
    //   float d;
    //   float t,s;
    //   DVector3 n,D,O;
    //   float ln;
    //   float in,out;
    //
    //   RC=org; RC.Subtract(&cylinder.position);
    //   n.Cross(&dir,&cylinder.axis);
    //
    //   ln=n.Length();
    //
    //   // Parallel? (?)
    //   if((ln<D3_EPSILON)&&(ln>-D3_EPSILON))
    //     return false;
    //
    //   n.Normalize();
    //
    //   d=fabs(RC.Dot(n));
    //
    //   if (d<=cylinder.radius)
    //   {
    //     O.Cross(&RC,&cylinder.axis);
    //     //TVector::cross(RC,cylinder._Axis,O);
    //     t=-O.Dot(n)/ln;
    //     //TVector::cross(n,cylinder._Axis,O);
    //     O.Cross(&n,&cylinder.axis);
    //     O.Normalize();
    //     s=fabs( sqrtf(cylinder.radius*cylinder.radius-d*d) / dir.Dot(O) );
    //
    //     in=t-s;
    //     out=t+s;
    //
    //     if (in<-D3_EPSILON)
    //     {
    //       if(out<-D3_EPSILON)
    //         return false;
    //       else lambda=out;
    //     } else if(out<-D3_EPSILON)
    //     {
    //       lambda=in;
    //     } else if(in<out)
    //     {
    //       lambda=in;
    //     } else
    //     {
    //       lambda=out;
    //     }
    //
    //     // Calculate intersection point
    //     newPosition=org;
    //     newPosition.x+=dir.x*lambda;
    //     newPosition.y+=dir.y*lambda;
    //     newPosition.z+=dir.z*lambda;
    //     DVector3 HB;
    //     HB=newPosition;
    //     HB.Subtract(&cylinder.position);
    //
    //     float scale=HB.Dot(&cylinder.axis);
    //     normal.x=HB.x-cylinder.axis.x*scale;
    //     normal.y=HB.y-cylinder.axis.y*scale;
    //     normal.z=HB.z-cylinder.axis.z*scale;
    //     normal.Normalize();
    //     return true;
    //   }
    //
    //   return false;
    // }











/* option shit
    Vector p = vectorSubstract(r.ori, pos);
    // coefficients for the intersection equation
    // got them mathematically intersecting the line equation with the cylinder equation
    float a = vectorDotProduct(r.dir, r.dir);
    float b = r.dir.x * p.x + r.dir.z * p.z;
  	float c = p.x * p.x + p.z * p.z - radius * radius;

    // std::cout << "height: " << height << endl;
    float delta = b*b - a*c;

    //use epsilon because of computation errors between floats
  	float epsilon = 0.00001;

  	// delta < 0 means no intersections
  	if (delta < epsilon) return false;

  	// nearest intersection
  	r.t = (-b - sqrtf (delta))/a;

  	// t<0 means the intersection is behind the ray origin
  	// which we don't want
  	if (r.t<=epsilon) return false;

    float y = p.y + r.t * r.dir.y;
    // float height = vectorLength(vectorSubstract(pos, pos2));


  	// check if we intersect one of the bases
  	if (y > height + epsilon || y < -epsilon) {
  		float dist;
  		bool b1 = intersect_base(r, pos2, dist);

  		if (b1) {
        r.t=dist;
      }

  		bool b2 = intersect_base(r, pos, dist);
  		if (b2 && dist>epsilon && r.t>=dist) {
        r.t=dist;
      }
      // std::cout << "intersecting cyl" << endl;

  		return b1 || b2;
  	}
    // std::cout << "intersection cylinder" << endl;
  	return true;

}

// Calculate intersection with the base having center c
// We do this by calculating the intersection with the plane
// and then checking if the intersection is within the base circle
bool Cylinder::intersect_base(Ray &r, const Vector& c, float& t) {

    Vector normal = getNormalInPoint(c);
    Vector p = vectorSubstract(r.ori, pos);

    float A = normal.x;
  	float B = normal.y;
  	float C = normal.z;
  	float D = - (A*(c.x-pos.x) +B*(c.y-pos.y)+C*(c.z-pos.z));

    if (vectorDotProduct(normal, r.dir) == 0) return false;

  	float dist = - (vectorDotProduct(normal,p)+D)/(vectorDotProduct(normal, r.dir));

  	float epsilon = 0.00001;

  	if (dist < epsilon) return false;

    Vector point = vectorAdd(vectorScale(r.dir, dist),p);
    // point.x = p.x +dist * r.dir.x;
    // point.y = p.y +dist * r.dir.y;
    // point.z = p.z +dist * r.dir.z;

    if (point.x*point.x + point.z*point.z - radius*radius > epsilon) return false;

  	t = dist;
  	return true;


}
// option shit
*/

  // Correct thing without optimization: for Sphere!
/*
    float a = vectorDotProduct(r.dir, r.dir);
    float b = vectorDotProduct(r.dir, vectorScale((vectorSubstract(r.ori, pos)), 2.f));
    float c = vectorDotProduct(vectorSubstract(r.ori, pos), vectorSubstract(r.ori, pos)) - radius*radius;

    // float *root;

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
    // Get lowest root: && r1 < maxR
    if (r1 > 0) {
      r.t = r1;
      return true;
    }
    // It is possible that we want x2 - this can happen
    // if x1 < 0 , ray origin inside Cylinder
    // && r2 < maxR
    if (r2 > 0) {
      r.t = r2;
      return true;
    }

*/



// Calculate the normal in a point on the surface
// it is a vertical vector in the bases and a vector
// having the direction of the vector from the axis to the point
Vector Cylinder::getNormalInPoint(Vector point) {
  /* option shit
    // Point is on one of the bases
    if (point.x < pos.x+radius && point.x > pos.x-radius && point.z < pos.z+radius && point.z > pos.z-radius)
    {
      float epsilon = 0.00001;

      if (point.y < pos.y + height + epsilon && point.y > pos.y + height - epsilon){
        return Vector(0,1,0);
      }
      if (point.y < pos.y + epsilon && point.y > pos.y - epsilon){
        return Vector(0,-1,0);
      }
    }

    // Point is on lateral surface
    Vector c0(pos.x, point.y, pos.z);

    Vector normal = vectorNormalize(vectorSubstract(point,c0));
  */
    Vector normal;

    if(latestValidIntersection == CYLINDER) {
      normal = vectorNormalize(vectorSubstract(point, projection));
      // std::cout << "norm in cylinder" << endl;
    }
    if(latestValidIntersection == DISK1) {
      normal = vectorNormalize(vectorSubstract(point,pos));
      // std::cout << "norm in disk1" << endl;
    }
    if(latestValidIntersection == DISK2) {
      normal = vectorNormalize(vectorSubstract(point,pos2));
      // std::cout << "norm in disk2" << endl;
    }
    return normal;

    // Vector normal = Vector((point.x - pos.x) / radius, (point.y - pos.y) / radius, (point.z - pos.z) / radius);
    // return normal; //TODO is this normalized already. I think so
}
