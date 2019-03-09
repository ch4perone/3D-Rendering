#include "Object.h"
#include "VectorMath.cpp"
#include <iostream>

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

    Vector ambientColor = vectorScale(vectorFromColor(material.color), material.diffuseComponent);
    Vector normalVector = getNormalInPoint(intersectionPoint); //TODO test this

    Vector sumOfReflectionColors = Vector(0,0,0);
    for (Light &light : activeLightSources) {
        Vector L = vectorNormalize(vectorDirection(intersectionPoint, light.pos));
        float nL = vectorDotProduct(vectorNormalize(normalVector), L);
        Vector lightVector = vectorScale(vectorFromColor(light.color), light.intensity); //TODO intensity????? ask the teacher
        Vector diffuseColor = vectorScale(lightVector, material.diffuseComponent * nL); //TODO what about diffuse color of the material?? mark

        sumOfReflectionColors = vectorAdd(sumOfReflectionColors, diffuseColor);

        /*
        Vector r = vectorScale(vectorSubstract(normalVector, L), 2*vectorDotProduct(L, normalVector));
        Vector v = vectorNormalize(vectorDirection(intersectionPoint, eyePosition));
        float rv = pow(vectorDotProduct(r,v), material.shininess);
        Vector specularColor = vectorScale(lightVector, material.specularComponent * rv);
        sumOfReflectionColors = vectorAdd(sumOfReflectionColors, specularColor);
        */
    }
    vectorPrint(sumOfReflectionColors, "reflection");

    Color shading = vectorToColor(vectorAdd(ambientColor, sumOfReflectionColors));
    vectorPrint(vectorFromColor(shading), "shading");
    return shading;
}

Vector Object::getNormalInPoint(Vector point) {
    std::cout << "Warning: getNormalInPoint() of super object called!" << '\n';
    return Vector(0,0,0);
}
