#include "Scene.h"
#include "defaultStructs.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

Scene::Scene(bool useGridAcceleration) : useGridAcceleration(useGridAcceleration) {

}

Camera *Scene::getCamera() {
    return camera;
}

bool Scene::load_nff(string path) {

    auto start = std::chrono::high_resolution_clock::now();

    //initialize fields
    Material currentMaterial;
    camera = new Camera();

    /*
     * Load file
     */

    ifstream f(path, ios::in);
    if (!f.good()) {
        cout << "Error: File not good. Check path: " << path << endl;
        return false;
    }

    /*
     * Iterate over file lines
     */

    cout << "-------- Scene ---------" << endl;
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
        if (label == "l") {
            cout << "load light source" << endl;
            Vector pos(values[0], values[1], values[2]);
            Color color(values[3], values[4], values[5]);
            lightSources.push_back(Light(pos, color));
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

            Sphere *sphere = new Sphere(pos, radius, currentMaterial, useGridAcceleration);
            objects.push_back(sphere);
        }

        if (label == "aabb") {
            cout << "load axis aligned box" << endl;
            Vector upper(values[0], values[1], values[2]);
            Vector lower(values[3], values[4], values[5]);

            AABB *aabb = new AABB(upper, lower, currentMaterial);
            objects.push_back(aabb);
        }

        if (label == "c") {
            cout << "load cylinder/cone" << endl;
            Vector pos(values[0], values[1], values[2]);
            float radius = values[3];
            Vector pos2(values[4], values[5], values[6]);
            float radius2 = values[7];

            Cylinder *cylinder = new Cylinder(pos, radius, pos2, radius2, currentMaterial, useGridAcceleration);
            objects.push_back(cylinder);
        }

        if (label == "pl") {
            cout << "load plane" << endl;
            Vector pos(values[0], values[1], values[2]);
            Vector pos2(values[3], values[4], values[5]);
            Vector pos3(values[6], values[7], values[8]);
            // float radius = values[3];

            Plane *plane = new Plane(pos, pos2, pos3, currentMaterial);
            objects.push_back(plane);
        }
        if (label == "p") {
            int numVertices = static_cast<int>(values[0]);
            cout << "load polygone primitiv of size " << numVertices << endl;
            vector<Vector> points;

            for (int i = 0; i < numVertices; ++i) {
                values.clear();

                getline(f, line);
                stringstream ss2(line);
                while(ss2 >> value) {
                    values.push_back(value);
                }
                Vector polygone(values[0], values[1], values[2]);
                points.push_back(polygone);
            }

            if (numVertices == 3) {
                Triangle *triangle = new Triangle(points[0], points[1], points[2], currentMaterial, useGridAcceleration);
                objects.push_back(triangle);
            } else {
                cout << "Warning: complex polygon object. No matching object class." << endl;
            }
        }
    }

    if(camera->completeSetup()) {
        cout << "camera setup complete" << endl;
        if(useGridAcceleration) {
            cout << "build Grid Acceleration Structure" << endl;
            grid = new Grid(objects);
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end-start;
        cout << "Scene prepping overhead: " << diff.count() << " s" << endl;
        return true;
    }
    return false;
}

vector<Object*> Scene::getObjects() {
    return objects;
}

Color Scene::getBackgroundColor() {
    return backgroundColor;
}

vector<Light> Scene::getLightSources() {
    return lightSources;
}

bool Scene::usesGridAcceleration() {
    return useGridAcceleration;
}

Grid *Scene::getGrid() {
    return grid;
}
