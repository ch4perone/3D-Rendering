#include "Camera.h"
#include <iostream>
#include <cmath>
#include "VectorMath.cpp"

Camera::Camera() {

}

Ray Camera::getPrimaryRay(int x, int y) {
    Vector ori = eye;
    Vector d = vectorAdd(vectorAdd(vectorScale(ze, -df), vectorScale(ye, h*(float(y + 0.5f)/ResY - 0.5f))), vectorScale(xe, w*(float(x + 0.5f)/ResX - 0.5f)));
    //ori = vectorAdd(eye, d);

    Ray primaryRay(ori, vectorNormalize(d));
    return primaryRay;
}

bool Camera::completeSetup() {
    fovy = static_cast<float>(fovy * M_PI / 180.f);
    df = vectorDistance(eye, at);
    h = 2.f * df * tan(fovy / 2.f);
    w = float(ResX) / float(ResY) * h;

    ze = vectorNormalize(vectorDirection(at, eye));
    xe = vectorNormalize(vectorCrossProduct(up, ze));
    ye = vectorNormalize(vectorCrossProduct(ze, xe));

    return true;
}

void Camera::printCameraSetup() {
    cout << "-------- Camera --------" << endl;
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
