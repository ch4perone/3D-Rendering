#include "Scene.h"

Scene::Scene() {

}

Camera *Scene::getCamera() {
    return camera;
}

bool Scene::load_nff(string path) {

    //TODO write PARSER for NFF

    return true;
}
