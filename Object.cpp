#include "Object.h"
#include "VectorMath.cpp"
#include <iostream>
#include <cmath>

Object::Object() {

}

Object::Object(Vector pos, Material material) : pos(pos), material(material) {

}

Material Object::getMaterial() {
    return material;
}

bool Object::intersect(Ray &r) {
    std::cout << "Warning: intersect() of super object called!" << '\n';
    return false;
}

Color Object::computeShading(Vector intersectionPoint, Vector eyePosition, vector<Light> &activeLightSources) {

    Vector ambientColor = vectorScale(vectorFromColor(material.color), material.ambientComponent);
    Vector normalVector = getNormalInPoint(intersectionPoint);

    Vector sumOfReflectionColors = Vector(0,0,0);
    for (Light &light : activeLightSources) {
        Vector L = vectorNormalize(vectorDirection(intersectionPoint, light.pos));
        float nL = vectorDotProduct(normalVector, L);
        Vector lightVector = vectorScale(vectorFromColor(light.color), light.intensity); //TODO intensity????? ask the teacher
        lightVector.x *= material.color.r;
        lightVector.y *= material.color.g;
        lightVector.z *= material.color.b;
        Vector diffuseColor = vectorScale(lightVector, material.diffuseComponent * nL);

        sumOfReflectionColors = vectorAdd(sumOfReflectionColors, diffuseColor);

        /*
         * Specular color
         */

        Vector r = vectorNormalize(vectorSubstract(vectorScale(normalVector, 2.f*vectorDotProduct(L, normalVector)), L));
        Vector v = vectorNormalize(vectorDirection(intersectionPoint, eyePosition));
        float rv = pow(fmaxf(0.f, vectorDotProduct(r, v)), material.shininess);
        //float rv = pow(vectorDotProduct(r,v), material.shininess);
        lightVector = vectorScale(vectorFromColor(light.color), light.intensity);
        Vector specularColor = vectorScale(lightVector, material.specularComponent * rv);
        sumOfReflectionColors = vectorAdd(sumOfReflectionColors, specularColor);

    }
    //vectorPrint(sumOfReflectionColors, "reflection");

    Color shading = vectorToColor(vectorAdd(ambientColor, sumOfReflectionColors));
    //vectorPrint(vectorFromColor(shading), "shading");
    return shading;
}

Vector Object::getNormalInPoint(Vector point) {
    std::cout << "Warning: getNormalInPoint() of super object called!" << '\n';
    return Vector(0,0,0);
}

bool Object::isReflective() {
    return getMaterial().specularComponent > 0.f;
}

bool Object::isTranslucid() {
    return getMaterial().transmittance > 0.f;
}

Vector Object::getReflectionInPoint(Vector point, Vector eyePosition, bool interior) {
    Vector V = vectorNormalize(vectorDirection(point, eyePosition));
    Vector normalVector = getNormalInPoint(point);
    if (interior) {
        normalVector = vectorScale(normalVector, -1.f);
    }
    Vector r = vectorSubstract(vectorScale(normalVector, 2.f*vectorDotProduct(V, normalVector)), V);

    return r;
}
