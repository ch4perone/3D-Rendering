#include "Camera.h"
#include <iostream>
#include "VectorMath.cpp"

Camera::Camera() {

}

Ray Camera::getPrimaryRay(int x, int y) {
    //TODO
    Vector ori = eye; // shouldn't this be the exact Pixel position in the hither plane?
    Vector d = vectorAdd(vectorAdd(vectorScale(ze, -df), vectorScale(ye, h*((y+0.5f)/ResY - 1.f/2.f))), vectorScale(xe, w*((x+0.5f)/ResX - 1.f/2.f)));


    Ray primaryRay(ori, d);
    return primaryRay;
}

bool Camera::completeSetup() {
    df = vectorDistance(eye, at);
    h = 2.f * df * tan(fovy / 2.f);
    w = float(ResX) / float(ResY) * h;

    ze = vectorNormalize(vectorDirection(at, eye));
    xe = vectorNormalize(vectorCrossProduct(up, ze));
    ye = vectorCrossProduct(ze, xe);

    return true;
}

void Camera::printCameraSetup() {
    cout << "Camera: " << endl;
    vectorPrint(eye, "eye");
    vectorPrint(at, "at");
    vectorPrint(up, "up");
    vectorPrint(xe, "xe");
    vectorPrint(ye, "ye");
    vectorPrint(ze, "ze");
    cout << "fovy: " << fovy << endl;
    cout << "hither: " << hither << endl;
    cout << "near: " << near << endl;
    cout << "far: " << far << endl;
    cout << "df: " << df << endl;
    cout << "h: " << h << endl;
    cout << "w: " << w << endl;
    cout << "ResX: " << ResX << " ResY: " << ResY << endl;


}
