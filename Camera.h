#ifndef PROJECT_CAMERA_H
#define PROJECT_CAMERA_H

#include "defaultStructs.h"

class Camera {

    Vector eye, at, up;
    float fovy;

    float near, far;
    int ResX, ResY;

    float w,h;
    Vector xe, ye,ze; //uvn


public:
    Ray PrimaryRay(int x, int y);

};


#endif //PROJECT_CAMERA_H
