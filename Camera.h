#ifndef PROJECT_CAMERA_H
#define PROJECT_CAMERA_H

#include "defaultStructs.h"

using namespace std;

/**
 * @class Camera
 * contains required fields and properties to describe the camera object in the scene.
 * contains function to compute PrimaryRays from eye position through the screen.
 */

class Camera {
public:
    Vector eye, at, up;
    float fovy;

    float hither;
    float near, far;
    float df;
    int ResX, ResY;

    float w,h;
    Vector xe, ye, ze; //uvn

    //Depth of field effects (manually set)
    float aperture = 0.04f;
    float distanceFocalPlane = 3.f; //Red carpet distances: 1.5 first | 3 middle range | 7 far

    Camera();
    bool completeSetup();
    void printCameraSetup();
    Ray getPrimaryRay(float x, float y);
    Ray getPrimaryRay(float x, float y, Vector2D eyeDiskOffset);


};


#endif //PROJECT_CAMERA_H
