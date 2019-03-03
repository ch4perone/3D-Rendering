#ifndef PROJECT_CAMERA_H
#define PROJECT_CAMERA_H

#include "defaultStructs.h"

class Camera {
public:
    Vector eye, at, up;
    float fovy;

    float hither;
    float near, far;
    float df;
    int ResX, ResY;

    float w,h;
    Vector xe, ye,ze; //uvn


    Camera();
    bool completeSetup();

    Ray getPrimaryRay(int x, int y);

};


#endif //PROJECT_CAMERA_H
