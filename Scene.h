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
// #include "Grid.h"
#include "AABB.h"


using namespace std;

/**
 * @class Scene
 * contains all objects and fields necessary for the renderer.
 * contains functions to load and access objects.
 */

class Scene {
    Camera* camera;
    vector<Object*> objects;
    vector<Light> lightSources;

    Color backgroundColor = Color(0, 0, 0);

    //Grid Acceleration Structure
    bool useGridAcceleration;
    // Grid *grid;

public:
    Scene(bool useGridAcceleration);
    bool load_nff(string path);

    //Getters
    Camera *getCamera();
    vector<Object*> getObjects(); //TODO make it reference vector<> &
    vector<Light> getLightSources();
    Color getBackgroundColor();
    // Grid *getGrid();
    bool usesGridAcceleration();
};


#endif //EXERCISE1_SCENE_H
