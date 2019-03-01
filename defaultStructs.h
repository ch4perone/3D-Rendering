#ifndef EXERCISE1_DEFAULTSTRUCTS_H
#define EXERCISE1_DEFAULTSTRUCTS_H


struct Vector {
    float x, y, z;

    Vector(float x, float y, float z) : x(x), y(y), z(z) {

    }
};

struct Color {
    float r,g,b;
    Color(float r, float g, float b) : r(r), g(g), b(b) {

    }
};

struct Ray {
    Vector ori;
    Vector dir;

    float ti;

    Ray(Vector ori, Vector dir) : ori(ori), dir(dir) {

    }

};

struct _Camera {

    Vector eye, at, up;
    float fovy;

    float near, far;
    int ResX, ResY;

    float w,h;
    Vector xe, ye,ze; //uvn

};

typedef struct _Camera Camera;


#endif //EXERCISE1_DEFAULTSTRUCTS_H
