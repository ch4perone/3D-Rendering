#include "Camera.h"
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
    h = static_cast<float>(2 * df * tan(fovy / 2.f));
    w = ResX / ResY * h;

    ze = vectorNormalize(vectorDirection(eye, at));
    xe = vectorNormalize(vectorCrossProduct(up, ze));
    ye = vectorCrossProduct(ze, xe);

    return true;
}
