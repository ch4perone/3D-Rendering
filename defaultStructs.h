#ifndef EXERCISE1_DEFAULTSTRUCTS_H
#define EXERCISE1_DEFAULTSTRUCTS_H


struct Vector {
    float x, y, z;

    Vector(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct Color {
    float r,g,b;
    Color(float r, float g, float b) : r(r), g(g), b(b) {}
};

struct Ray {
    Vector ori;
    Vector dir;

    float t;

    Ray(Vector ori, Vector dir) : ori(ori), dir(dir) {}

};

struct Material {
    Color color;
    float diffuseComponent;
    float specular;
    float shininess;
    float transmittance;
    float indexOfRefraction;

    Material() : color(Color(0,0,0)) {};
    Material(Color color, float diffuseComponent, float specular, float shininess, float transmittance, float indexOfRefraction) : color(color), diffuseComponent(diffuseComponent), specular(specular), shininess(shininess), transmittance(transmittance), indexOfRefraction(indexOfRefraction) {}

    // Fill color and shading parameters. Description:
// "f" red green blue Kd Ks Shine T index_of_refraction
// Format:
// f %g %g %g %g %g %g %g %g
// RGB is in terms of 0.0 to 1.0.
// Kd is the diffuse component, Ks the specular, Shine is the Phong cosine
// power for highlights, T is transmittance (fraction of contribution of the
// transmitting ray). Usually, 0 <= Kd <= 1 and 0 <= Ks <= 1, though it is not required that Kd + Ks == 1. Note that transmitting objects ( T > 0 ) are considered to have two sides for algorithms that need these (normally objects have one side).
// The fill color is used to color the objects following it until a new color is assigned.

};




#endif //EXERCISE1_DEFAULTSTRUCTS_H
