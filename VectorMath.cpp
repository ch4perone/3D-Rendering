#include <iostream>
#include <string>
#include <cmath>
#include "defaultStructs.h"

struct Vector;

/**
 * @file vectorMath
 * contains math operation for Vector class
 */

//TODO this whole thing might be slow af


static float vectorLength(Vector v) {
    return static_cast<float>(sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

static Vector vectorAdd(Vector v1, Vector v2) {
    return Vector(v1.x + v2.x, v1.y + v2.y,  v1.z + v2.z);
}

static Vector vectorAddToAllAxis(Vector v, float value) {
    return Vector(v.x + value, v.y + value,  v.z + value);
}

static Vector vectorSubstract(Vector v1, Vector v2) {
    return Vector(v1.x - v2.x, v1.y - v2.y,  v1.z - v2.z);
}

static Vector vectorDirection(Vector from, Vector to) {
    return Vector(to.x - from.x, to.y - from.y,  to.z - from.z);
}

static float vectorDistance(Vector v1, Vector v2) {
    float squaredDist = (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y) + (v1.z - v2.z) * (v1.z - v2.z);
    return static_cast<float>(sqrt(squaredDist));
}

static Vector vectorScale(Vector v, float scale) {
    return Vector(v.x * scale, v.y * scale,  v.z * scale);
}

static Vector vectorCrossProduct(Vector v1, Vector v2) {
    return Vector(v1.y*v2.z-v1.z*v2.y, v1.z*v2.x- v1.x*v2.z, v1.x*v2.y-v1.y*v2.x);
}

static Vector vectorNormalize(Vector v) {
    return vectorScale(v, 1.f/vectorLength(v));
}

static float vectorDotProduct(Vector v1, Vector v2) {
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

static void vectorPrint(Vector v) {
  std::cout << "Vector: " << v.x << " " << v.y << " " << v.z << std::endl;
}

static void vectorPrint(Vector v, std::string name) {
    std::cout << name << ": " << v.x << " " << v.y << " " << v.z << std::endl;
}

static Vector vectorFromColor(Color c) {
    return Vector(c.r, c.g, c.b);
}

static Color vectorToColor(Vector v) {
    return Color(v.x, v.y, v.z);
}
