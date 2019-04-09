#include "Camera.h"
#include <iostream>
#include <cmath>
#include "VectorMath.cpp"
#include "Plane.h"

Camera::Camera() {

}

Ray Camera::getPrimaryRay(float x, float y) {
    Vector ori = eye;
    Vector d = vectorAdd(vectorAdd(vectorScale(ze, -df), vectorScale(ye, h*(y/ResY - 0.5f))),vectorScale(xe, w*(x/ResX - 0.5f)));

    Ray primaryRay(ori, vectorNormalize(d));
    return primaryRay;
}

Ray Camera::getPrimaryRay(float x, float y, Vector2D eyeDiskOffset) {
    Vector origin = eye;
    Vector xeOffset = vectorScale(xe, eyeDiskOffset.x * aperture);
    Vector yeOffset = vectorScale(ye, eyeDiskOffset.y * aperture);
    origin = vectorAdd(vectorAdd(origin, xeOffset), yeOffset);

    Vector centerToFocalPoint = vectorAdd(vectorAdd(vectorScale(ze, -distanceFocalPlane), vectorScale(ye, (h*(y/ResY - 0.5f))*(distanceFocalPlane/df) )),vectorScale(xe, (w*(x/ResX - 0.5f))*(distanceFocalPlane/df)));
    Vector focalPoint = vectorAdd(eye, centerToFocalPoint);
    Vector direction = vectorDirection(origin, focalPoint);


    Ray primaryRay(origin, vectorNormalize(direction));
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
