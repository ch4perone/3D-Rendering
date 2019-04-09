#include <random>

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <cassert>
#include "Scene.h"
#include "RayCast.h"
#include "VectorMath.cpp"
#include "RandomSampler.h"


/*
 * For linux:
 */

//Compile command
//g++ main.cpp Scene.cpp Camera.cpp Object.cpp Sphere.cpp Plane.cpp Triangle.cpp VectorMath.cpp RayCast.cpp Cylinder.cpp RandomSampler.cpp -o app -lglut -lGLU -lGL

//Includes
#include <GL/glut.h>
#include <algorithm>

/*
 * For macOS
 */

//Compile command
//g++ main.cpp Scene.cpp Camera.cpp Object.cpp Sphere.cpp Plane.cpp Triangle.cpp VectorMath.cpp RayCast.cpp Cylinder.cpp -o app -framework OpenGL -framework GLUT -Wno-deprecated

//Includes
//#include <OpenGL/gl.h>
//#include <OpenGl/glu.h>
//#include <GLUT/glut.h>

bool MojaveWorkAround = false; //Set to true for macOS Mojave.

#define MAX_DEPTH 4

Scene* scene = NULL;
string scene_path = "./scenes/balls_low_row.nff";
int RES_X, RES_Y;
bool ANTIALIASING = true;
bool SOFTSHADOWS = true;
bool DEPTHOFFIELD = true;
int n = 4;


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
            Vector dir = vectorNormalize(vectorDirection(intersectionPoint, lightPosition));
            float lightDistance = vectorDistance(intersectionPoint, lightPosition);

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

    #pragma omp parallel for
    for (int y = 0; y < RES_Y; y++)
    {
        for (int x = 0; x < RES_X; x++)
        {
            if (ANTIALIASING) {

                //Jitter ray (pixelJitter), and source lights (lightJitter)
                vector<Vector2D> pixelJitter = RandomSampler::jitter2D(n);
                vector<Vector2D> lightJitter = RandomSampler::jitter2D(n);
                //vector<Vector2D> eyeDiskOffsets = RandomSampler::jitter2D(n);
                vector<Vector2D> eyeDiskOffsets = RandomSampler::getPointsInUnitDisk(n*n);
                shuffle(lightJitter.begin(), lightJitter.end(), std::mt19937(std::random_device()()));
                shuffle(eyeDiskOffsets.begin(), eyeDiskOffsets.end(), std::mt19937(std::random_device()()));

                Color pixelColor = Color(0,0,0); //init black
                for(int i = 0; i < pixelJitter.size(); ++i) {
                    Vector2D offset = pixelJitter[i];
                    if (DEPTHOFFIELD) {
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
                Ray ray = scene->getCamera()->getPrimaryRay(x, y);
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

    scene = new Scene();
    if(!(scene->load_nff(scene_path))) {
        return 0;
    }

    RandomSampler::initSeed();
    float sum = 0;


    for (int i = 0; i < 100; ++i) {
        sum+=RandomSampler::getFloatInRange(0, 1.f);
    }

    cout << sum / 100.f << endl;
    RES_X = scene->getCamera()->ResX;
    RES_Y = scene->getCamera()->ResY;
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
