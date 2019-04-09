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
    Vector ori = eye;
    Vector xeOffset = vectorScale(xe, eyeDiskOffset.x * aperture);
    Vector yeOffset = vectorScale(ye, eyeDiskOffset.y * aperture);

    ori = vectorAdd(vectorAdd(ori, xeOffset), yeOffset);

    //Vector d_center = vectorAdd(vectorAdd(vectorScale(ze, -df), vectorScale(ye, h*(y/ResY - 0.5f))),vectorScale(xe, w*(x/ResX - 0.5f)));
    Vector center_to_focal_point = vectorAdd(vectorAdd(vectorScale(ze, -distanceFocalPlane), vectorScale(ye, (h*(y/ResY - 0.5f))*(distanceFocalPlane/df) )),vectorScale(xe, (w*(x/ResX - 0.5f))*(distanceFocalPlane/df)));
    Vector focal_point = vectorAdd(eye, center_to_focal_point);

    Vector direction = vectorDirection(ori, focal_point);


    Ray primaryRay(ori, vectorNormalize(direction));
    return primaryRay;



    /*Vector ps = vectorAdd(eye, d_center);
    Vector focalPoint = Vector(ps.x * (distanceFocalPlane / df), ps.y * (distanceFocalPlane / df), -distanceFocalPlane);
    //Vector d_focal = vectorDirection(ori, focalPoint);
    Vector focalDirection = vectorAdd(
                            vectorAdd(
                                    vectorScale(xe, focalPoint.x - eyeDiskOffset.x),
                                    vectorScale(ye, focalPoint.y - eyeDiskOffset.y)),
                                    vectorScale(ze, -distanceFocalPlane)
                            );


    Vector planeCenter = vectorAdd(eye, vectorScale(ze, -distanceFocalPlane));
    Plane *focalPlane = new Plane(planeCenter, vectorAdd(planeCenter, xe), vectorAdd(planeCenter, ye), Material());
    Ray centerRay = Ray(eye, vectorNormalize(d_center));
    focalPlane->intersect(centerRay);
    Vector focalPoint = vectorAdd(centerRay.ori, vectorScale(centerRay.dir, centerRay.t));
    Vector focalDirection = vectorDirection(ori, focalPoint);

    Ray primaryRay(ori, vectorNormalize(focalDirection));
    return primaryRay;
    */
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
