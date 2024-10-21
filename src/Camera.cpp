#include "Camera.h"
#include <iostream>
#include <cmath>
#include "Vector.h"
#include "Plane.h"

Camera::Camera() {

}

Ray Camera::getPrimaryRay(float x, float y) {
    Vector ori = eye;
    Vector d = (ze * -df) + (ye * (h*(y/ResY - 0.5f))) + (xe * (w*(x/ResX - 0.5f)));

    Ray primaryRay(ori, d.normalize());
    return primaryRay;
}

Ray Camera::getPrimaryRay(float x, float y, Vector2D eyeDiskOffset) {
    Vector origin = eye;
    Vector xeOffset = xe * (eyeDiskOffset.x * aperture);
    Vector yeOffset = ye * (eyeDiskOffset.y * aperture);
    origin = origin + xeOffset + yeOffset;

    Vector centerToFocalPoint = (ze * -distanceFocalPlane) + (ye * ((h*(y/ResY - 0.5f))*(distanceFocalPlane/df))) + (xe * ((w*(x/ResX - 0.5f))*(distanceFocalPlane/df)));
    Vector focalPoint = eye + centerToFocalPoint;
    Vector direction = origin.directionTo(focalPoint);


    Ray primaryRay(origin, direction.normalize());
    return primaryRay;
}

bool Camera::completeSetup() {
    fovy = static_cast<float>(fovy * M_PI / 180.f);
    df = eye.distance(at);
    h = 2.f * df * tan(fovy / 2.f);
    w = float(ResX) / float(ResY) * h;

    ze = at.directionTo(eye).normalize();
    xe = (up % ze).normalize();
    ye = (ze % xe).normalize();

    return true;
}

void Camera::printCameraSetup() {
    cout << "-------- Camera --------" << endl;
    cout << "eye: "; eye.display();
    cout << "at: "; at.display();
    cout << "up: "; up.display();
    cout << "xe: "; xe.display();
    cout << "ye: "; ye.display();
    cout << "ze: "; ze.display();
    cout << "fovy: " << fovy << endl;
    cout << "hither: " << hither << endl;
    cout << "near: " << near << endl;
    cout << "far: " << far << endl;
    cout << "df: " << df << endl;
    cout << "h: " << h << endl;
    cout << "w: " << w << endl;
    cout << "aperture: " << aperture << endl;
    cout << "focal: " << distanceFocalPlane << endl;
    cout << "ResX: " << ResX << " ResY: " << ResY << endl;
}
