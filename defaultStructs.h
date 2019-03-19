#ifndef EXERCISE1_DEFAULTSTRUCTS_H
#define EXERCISE1_DEFAULTSTRUCTS_H

/**
 * @headerfile defaultStructs
 * defines numerous structures used for the ray tracer.
 * Structures are mainly used to store properties and feature no to only a few methods.
 */

struct Vector {
    float x, y, z;
    bool initialized;

    Vector() : initialized(false) {}
    Vector(float x, float y, float z) : x(x), y(y), z(z), initialized(true) {}
};

struct Color {
    float r,g,b;

    Color(float r, float g, float b) : r(r), g(g), b(b) {}

    void scale(float factor) {
        r *= factor;
        g *= factor;
        b *= factor;
    }
    void addColor(Color color) {
        r += color.r;
        g += color.g;
        b += color.b;
    }
};

struct Ray {
    Vector ori;
    Vector dir;

    float t;
    bool interiorMedium;

    Ray(Vector ori, Vector dir, bool interiorMedium = false) : ori(ori), dir(dir), interiorMedium(interiorMedium) {

    }

    //Move ray a tiny instance along its direction
    void glitchForward() {
        ori.x = ori.x + dir.x*0.0001f;
        ori.y = ori.y + dir.y*0.0001f;
        ori.z = ori.z + dir.z*0.0001f;
    }
};

struct Light {
    Vector pos;
    Color color;
    float intensity = 1.f;// 0.25f;

    Light(Vector pos, Color color) : pos(pos), color(color) {}
};

struct Material {
    Color color;
    float ambientComponent = 0.f;
    float diffuseComponent;
    float specularComponent;
    float shininess;
    float transmittance;
    float indexOfRefraction;

    Material() : color(Color(0,0,0)) {};
    Material(Color color, float diffuseComponent, float specularComponent, float shininess, float transmittance, float indexOfRefraction) : color(color), diffuseComponent(diffuseComponent), specularComponent(specularComponent), shininess(shininess), transmittance(transmittance), indexOfRefraction(indexOfRefraction) {}

};




#endif //EXERCISE1_DEFAULTSTRUCTS_H
