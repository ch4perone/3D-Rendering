#include "Scene.h"
#include "defaultStructs.h"
#include <iostream>
#include <fstream>
#include <sstream>

Scene::Scene() {

}

Camera *Scene::getCamera() {
    return camera;
}

bool Scene::load_nff(string path) {

    //TODO write PARSER for NFF


    //fields
    Material currentMaterial;
    camera = new Camera();

    ifstream f(path, ios::in);
    if (!f.good()) {
        cout << "Error: File not good. Check path: " << path << endl;
        return false;
    }
    while(!f.eof()) {

        //Read line from file
        string line;
        getline(f, line);
        stringstream ss(line);

        //Parse label and values from line
        string label;
        float value;
        vector<float> values;

        ss >> label;
        while(ss >> value) {
            values.push_back(value);
        }

        //Evaluate label and create Object
        if (label == "b") {
            cout << "load background color" << endl;
            backgroundColor = Color(values[0], values[1], values[2]);
        }
        if (label == "from") {
            camera->eye = Vector(values[0], values[1], values[2]);
        }
        if (label == "at") {
            camera->at = Vector(values[0], values[1], values[2]);
        }
        if (label == "up") {
            camera->up = Vector(values[0], values[1], values[2]);
        }
        if (label == "angle") {
            camera->fovy = values[0];
        }
        if (label == "hither") {
            camera->hither = values[0];
        }
        if (label == "resolution") {
            camera->ResX = static_cast<int>(values[0]);
            camera->ResY = static_cast<int>(values[1]);
        }
        if (label == "f") {
            cout << "load material" << endl;
            Color color(values[0], values[1], values[2]);
            currentMaterial = Material(color, values[3], values[4], values[5], values[6], values[7]);
        }
        if (label == "s") {
            cout << "load sphere" << endl;
            Vector pos(values[0], values[1], values[2]);
            float radius = values[3];

            Sphere *sphere = new Sphere(pos, radius, currentMaterial);
            objects.push_back(sphere);
        }
    }

    if(camera->completeSetup()) {
        cout << "camera setup complete" << endl;
    }
    return true;
}

vector<Object*> Scene::getObjects() {
    return objects;
}

Color Scene::getBackgroundColor() {
    return backgroundColor;
}
