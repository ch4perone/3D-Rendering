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
    Vector xe, ye,ze; //uvn

    //Depth of field effects (manually set)
    float aperture = 0.5f;
    float distanceFocalPlane = 2.88f;

    Camera();
    bool completeSetup();
    void printCameraSetup();
    Ray getPrimaryRay(float x, float y);
    Ray getPrimaryRay(float x, float y, Vector2D eyeDiskOffset);


};


#endif //PROJECT_CAMERA_H
