#ifndef EXERCISE1_SCENE_H
#define EXERCISE1_SCENE_H

#include <vector>
#include "defaultStructs.h"

using namespace std;

class Scene {

    vector<Vector> objects;
    Camera * camera;

public:

    Scene() {};
    Camera *getCamera() {
        return camera;
    }



private:



};


#endif //EXERCISE1_SCENE_H
