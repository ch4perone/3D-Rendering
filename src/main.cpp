#include <random>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <cassert>
#include "Scene.h"
#include "RayCast.h"
#include "Vector.h"
#include "RandomSampler.h"


/*
 * For linux:
 */

//Compile command
//g++ main.cpp Scene.cpp Camera.cpp Object.cpp Sphere.cpp Plane.cpp Triangle.cpp VectorMath.cpp RayCast.cpp Cylinder.cpp AABB.cpp RandomSampler.cpp Cell.cpp Grid.cpp Vector.cpp -o app -lglut -lGLU -lGL --std=c++17

//Includes
#include <GL/glut.h>

/*
 * For macOS
 */

//Compile command
//g++ main.cpp Scene.cpp Camera.cpp Object.cpp Sphere.cpp Plane.cpp Triangle.cpp VectorMath.cpp RayCast.cpp Cylinder.cpp AABB.cpp Vector.cpp Cell.cpp Grid.cpp RandomSampler.cpp -o app -framework OpenGL -framework GLUT -Wno-deprecated --std=c++17

//Includes
// #include <OpenGL/gl.h>
// #include <OpenGl/glu.h>
// #include <GLUT/glut.h>

bool MojaveWorkAround = false; //Set to true for macOS Mojave.

#define MAX_DEPTH 4

Scene* scene = NULL;
string scene_path = "./scenes/dof_example.nff";
int RES_X = 0;
int RES_Y = 0;
bool ANTIALIASING = true;
bool SOFTSHADOWS = true;
bool DEPTH_OF_FIELD = true;
bool GRID_ACCELERATION = true;
float APERTURE = -1.f;
float DISTANCE_FOCAL_PLANE = -1.f;
int n = 4;

//Argument Parsing
void parse_args(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--scene" && i + 1 < argc) {
            scene_path = argv[++i];
        } else if (arg == "--res_x" && i + 1 < argc) {
            RES_X = std::stoi(argv[++i]);
        } else if (arg == "--res_y" && i + 1 < argc) {
            RES_Y = std::stoi(argv[++i]);
        } else if (arg == "--antialiasing" && i + 1 < argc) {
            ANTIALIASING = (std::stoi(argv[++i]) != 0);
        } else if (arg == "--softshadows" && i + 1 < argc) {
            SOFTSHADOWS = (std::stoi(argv[++i]) != 0);
        } else if (arg == "--depth_of_field" && i + 1 < argc) {
            DEPTH_OF_FIELD = (std::stoi(argv[++i]) != 0);
        } else if (arg == "--aperture" && i + 1 < argc) {
            APERTURE = std::stof(argv[++i]);
        } else if (arg == "--focal_distance" && i + 1 < argc) {
            DISTANCE_FOCAL_PLANE = std::stof(argv[++i]);
        } else if (arg == "--grid_acceleration" && i + 1 < argc) {
            GRID_ACCELERATION = (std::stoi(argv[++i]) != 0);
        } else if (arg == "--n" && i + 1 < argc) {
            n = std::stoi(argv[++i]);
        } else if (arg == "-h" || arg == "--help") {
            std::cout << "Usage:\n"
                      << "--scene [path]           : Set scene file path\n"
                      << "--res_x [value]          : Set custom resolution width\n"
                      << "--res_y [value]          : Set custom resolution height\n"
                      << "--antialiasing [0/1]     : Enable or disable antialiasing\n"
                      << "--n [value]              : Set number n of pixel jitter for antialiasing\n"
                      << "--softshadows [0/1]      : Enable or disable soft shadows\n"
                      << "--depth_of_field [0/1]   : Enable or disable depth of field\n"
                      << "--aperture [value]       : Aperture for depth of field (Default 0.04)\n"
                      << "--focal_distance [value] : Distance to focal plane for depth of field (Default 3.0)\n"
                      << "--grid_acceleration [0/1]: Enable or disable grid acceleration\n"
                      << "-h                       : Display this help message\n";
            exit(0);
        }
    }
}


//Reshape function (given)
void reshape(int w, int h)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, RES_X-1, 0, RES_Y -1, 100, -100);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
}

//Turner W. Ray Tracing algorithm
Color rayTracing(Ray ray, int depth, float indexOfRefraction, Vector2D lightJitterOffset) {

    /*
     * Cast Ray
     */

    RayCast rayCast(ray, scene);
    if (rayCast.doesIntersect) {
        Object *frontObject = rayCast.frontObject;
        Vector intersectionPoint = rayCast.intersectionPoint;

        //Compute Shading
        vector<Light> activeLights; //container for not occluded lights
        for (Light &light : scene->getLightSources()) {
            Vector lightPosition = light.pos;
            if (SOFTSHADOWS) {
                lightPosition = light.getJitteredPosition(lightJitterOffset);
            }
            Vector dir = intersectionPoint.directionTo(lightPosition).normalize();
            float lightDistance = intersectionPoint.distance(lightPosition);

            Ray shadowRay = Ray(intersectionPoint, dir);
            shadowRay.glitchForward();

            if(rayCast.castNewRay(shadowRay, scene)) {
                if (rayCast.distanceToIntersection < lightDistance) {
                    continue;
                }
            }
            activeLights.push_back(light);
        }
        Color color = frontObject->computeShading(intersectionPoint, ray.ori, activeLights);

        //Recursion halt condition
        if (depth >= MAX_DEPTH) {
            return color;
        }

        /*
         * Cast secondary Rays
         */

        //Reflection
        if (frontObject->isReflective()) {
            Vector direction = frontObject->getReflectionInPoint(intersectionPoint, ray.ori, ray.interiorMedium);
            Ray reflectedRay(intersectionPoint, direction);
            reflectedRay.glitchForward();

            Color reflectedColor = rayTracing(reflectedRay, depth + 1, indexOfRefraction, lightJitterOffset);
            reflectedColor.scale(frontObject->getMaterial().specularComponent);
            color.addColor(reflectedColor);
        }

        //Refraction
        if(frontObject->isTranslucid()) {
            Vector direction = frontObject->getRefractionDirectionInPoint(intersectionPoint, ray.ori, indexOfRefraction, ray.interiorMedium);
            if (!direction.initialized) { //Catch invalid vectors (eg. from total reflection)
                return color;
            }

            Ray refractedRay(intersectionPoint, direction);
            refractedRay.glitchForward();
            refractedRay.interiorMedium = !ray.interiorMedium;

            Color refractionColor = rayTracing(refractedRay, depth + 1, frontObject->getMaterial().indexOfRefraction, lightJitterOffset);
            refractionColor.scale(frontObject->getMaterial().transmittance);
            color.addColor(refractionColor);
        }

        return color;
    }

    return scene->getBackgroundColor();
}

void drawSceneParallelized()
{
    /*
     * Render pixel color (parallelized)
     */

    cout << "-------- Rendering ---------" << endl;
    vector<vector<Color> > renderedColors(RES_Y, vector<Color>(RES_X, Color(1,1,1)));
    auto start = std::chrono::high_resolution_clock::now();

    //Select number of threads (otherwise all cores will be used)
    //#pragma omp parallel num_threads(4)

    #pragma omp parallel for num_threads(8)
    for (int y = 0; y < RES_Y; y++)
    {
        for (int x = 0; x < RES_X; x++)
        {
            if (ANTIALIASING) {

                //Jitter ray (pixelJitter), and source lights (lightJitter)
                vector<Vector2D> pixelJitter = RandomSampler::jitter2D(n);
                vector<Vector2D> lightJitter = RandomSampler::jitter2D(n);
                vector<Vector2D> eyeDiskOffsets = RandomSampler::getPointsInUnitDisk(n*n);
                shuffle(lightJitter.begin(), lightJitter.end(), std::mt19937(std::random_device()()));
                shuffle(eyeDiskOffsets.begin(), eyeDiskOffsets.end(), std::mt19937(std::random_device()()));

                Color pixelColor = Color(0,0,0); //init black
                for(int i = 0; i < pixelJitter.size(); ++i) {
                    Vector2D offset = pixelJitter[i];
                    if (DEPTH_OF_FIELD) {
                        Ray ray = scene->getCamera()->getPrimaryRay(x + offset.x, y + offset.y, eyeDiskOffsets[i]);
                        pixelColor.addColor(rayTracing(ray, 1, 1.0f, lightJitter[i]));
                    } else {
                        Ray ray = scene->getCamera()->getPrimaryRay(x + offset.x, y + offset.y);
                        pixelColor.addColor(rayTracing(ray, 1, 1.0f, lightJitter[i]));
                    }
                }
                pixelColor.scale(1.f / float(n*n));
                renderedColors[y][x] = pixelColor;


            } else {
                Ray ray;
                #pragma omp critical
                {
                    ray = scene->getCamera()->getPrimaryRay(x, y);
                }    
                Color pixelColor = rayTracing(ray, 1, 1.0f, Vector2D());
                renderedColors[y][x] = pixelColor;
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    cout << "Rendering computation time: " << diff.count() << " s" << endl;

    /*
     * Draw pixel colors
     */

    for (int y = 0; y < RES_Y; ++y) {
        for (int x = 0; x < RES_X; ++x) {
            Color pixelColor = renderedColors[y][x];
            glBegin(GL_POINTS);
            glColor3f(pixelColor.r, pixelColor.g, pixelColor.b);
            glVertex2f(x, y);
        }
    }

    glEnd();
    glFlush();
    printf("Terminated!\n");

    /*
     * Fix Display Error for macOS Mojave
     */

    if(MojaveWorkAround){
        glutReshapeWindow(0.99 * RES_X,0.99 * RES_Y);
        //Necessary for Mojave. Has to be different dimensions than in glutInitWindowSize();
        // However, will result in re-rendering.
        MojaveWorkAround = false;
    }
}


int main(int argc, char**argv)
{
    parse_args(argc, argv);

    scene = new Scene(GRID_ACCELERATION);
    if(!(scene->load_nff(scene_path))) {
        return 0;
    }

    RandomSampler::initSeed();

    if (RES_X != 0 && RES_Y != 0) { // Override Camera resolution with user input
        scene->getCamera()->ResX = RES_X;
        scene->getCamera()->ResY = RES_Y;
    } else {
        RES_X = scene->getCamera()->ResX;
        RES_Y = scene->getCamera()->ResY;
    }
    if (APERTURE >= 0) {
        scene->getCamera()->aperture = APERTURE;
    }
    if (DISTANCE_FOCAL_PLANE >= 0) {
        scene->getCamera()->distanceFocalPlane = DISTANCE_FOCAL_PLANE;
    }

    scene->getCamera()->printCameraSetup();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(RES_X, RES_Y);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Group 14: Ray Tracing");
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glutReshapeFunc(reshape);
    glutDisplayFunc(drawSceneParallelized);
    glDisable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
