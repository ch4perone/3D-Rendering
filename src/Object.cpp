#include "Object.h"
#include "Vector.h"
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
    if(rayInMailbox(r)) {
        return true;
    }
    std::cout << "Warning: intersect() of super object called!" << '\n';
    return false;
}

Color Object::computeShading(Vector intersectionPoint, Vector eyePosition, vector<Light> &activeLightSources) {

    /*
     * Note that Colors are converted to Vectors to use vector operation (Dot/Cross-product etc.)
     */


     // Ambient Color
     // > added ambientComponent to Material to get agency over ambient color (currently set to 0)
    Vector ambientColor = material.color.toVector() * material.ambientComponent;
    Vector normalVector = getNormalInPoint(intersectionPoint);

    Vector sumOfReflectionColors = Vector(0,0,0);
    for (Light &light : activeLightSources) {

        //Diffuse Color
        Vector L = intersectionPoint.directionTo(light.pos).normalize();
        float nL = normalVector.dot_product(L);
        Vector lightVector = light.color.toVector() * light.intensity; //light intensity optional, currently set to 1.f
        lightVector.x *= material.color.r;
        lightVector.y *= material.color.g;
        lightVector.z *= material.color.b;
        Vector diffuseColor = lightVector * (material.diffuseComponent * nL);
        sumOfReflectionColors += diffuseColor;

        //Specular Color
        Vector r = ((normalVector * (2.f*(L.dot_product(normalVector)))) - L).normalize();
        Vector v = intersectionPoint.directionTo(eyePosition).normalize();
        float rv = pow(fmaxf(0.f, (r.dot_product(v))), material.shininess);
        lightVector = light.color.toVector() * light.intensity;
        Vector specularColor = lightVector * (material.specularComponent * rv);
        sumOfReflectionColors += specularColor;
    }

    Color shading = Color(ambientColor + sumOfReflectionColors);
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
    Vector V = point.directionTo(eyePosition);
    V.normalize();
    Vector normalVector = getNormalInPoint(point);
    if (interior) {
        normalVector *= -1.f;
    }
    Vector r = (normalVector * (2.f*(V.dot_product(normalVector))) - V);
    return r;
}

Vector Object::getRefractionDirectionInPoint(Vector point, Vector eyePosition, float indexOfRefraction, bool interior) {
    Vector v = point.directionTo(eyePosition).normalize();
    Vector normal = getNormalInPoint(point);
    float iorMedium = getMaterial().indexOfRefraction;
    if (interior) {
        normal *= -1.f;
        iorMedium = 1;
    }

    if(v.dot_product(normal) < 0) {
        return Vector();
    }

    Vector v_t = (normal * v.dot_product(normal)) - v;
    float sinTeta_i = v_t.length();
    float sinTeta_t = (indexOfRefraction / iorMedium) * sinTeta_i;
    if(abs(sinTeta_t) > 1.f) { //total internal reflection
        return Vector();
    }
    float cosTeta_t = sqrtf(1.f - sinTeta_t * sinTeta_t);

    Vector R = (v_t.normalize() * sinTeta_t) + (normal * (-1.f * cosTeta_t));

    return R;

}

AABB* Object::getBoundingBox() {
  return boundingBox;
}

bool Object::rayInMailbox(Ray &ray) {
    if(ray.id == recentRayId) {
        ray.t = recentRayDistance;
        return true;
    }
    return false;
}
