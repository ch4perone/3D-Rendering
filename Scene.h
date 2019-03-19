#ifndef EXERCISE1_SCENE_H
#define EXERCISE1_SCENE_H

#include <vector>
#include <string>
#include "defaultStructs.h"
#include "Camera.h"
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Cylinder.h"

using namespace std;

class Scene {

    Camera* camera;
    vector<Object*> objects;
    vector<Light> lightSources;

    Color backgroundColor = Color(0, 0, 0);

public:

    Scene();

    bool load_nff(string path);

    //Getter
    Camera *getCamera();
    vector<Object*> getObjects();
    vector<Light> getLightSources();

    Color getBackgroundColor();


private:



};


#endif //EXERCISE1_SCENE_H
