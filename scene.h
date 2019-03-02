#ifndef EXERCISE1_SCENE_H
#define EXERCISE1_SCENE_H

#include <vector>
#include <string>
#include "defaultStructs.h"
#include "Camera.h"

using namespace std;

class Scene {

    vector<Vector> objects;
    Camera * camera;
    Color backgroundColor = Color(0, 0, 0);

public:

    Scene();

    bool load_nff(string path);

    //Getter
    Camera *getCamera();



private:



};


#endif //EXERCISE1_SCENE_H
