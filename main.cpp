#include <stdlib.h>
// #include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include "Scene.h"
#include "RayCast.h"
#include "VectorMath.cpp"
// g++ main.cpp Scene.cpp Camera.cpp Object.cpp Sphere.cpp Plane.cpp VectorMath.cpp RayCast.cpp  -o app -framework OpenGL -framework GLUT -Wno-deprecated
// g++ main.cpp Scene.cpp Camera.cpp Object.cpp Sphere.cpp Plane.cpp VectorMath.cpp RayCast.cpp -o app -lglut -lGLU -lGL
// ... -lGLEW

#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>


#define MAX_DEPTH 6

Scene* scene = NULL;
int RES_X, RES_Y;

bool MojaveWorkAround = 1;

void reshape(int w, int h)
{
    // glutReshapeWindow (RES_X, RES_Y);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, RES_X-1, 0, RES_Y -1, 100, -100);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    // glutReshapeWindow (RES_X, RES_Y);
}

// Draw function by primary ray casting from the eye towards the scene's objects
Color rayTracing(Ray ray, int depth, float indexOfRefraction) {

    /*
     * Cast Ray
     */

    RayCast rayCast(ray, scene);
    if (rayCast.doesIntersect) {

        //Compute Shading
        float shittyLightThing = 0;
        Vector ori = rayCast.intersectionPoint;
        for (Light &light : scene->getLightSources()) {
            Vector dir = vectorDirection(ori, light.pos);
            float lightDistance = vectorDistance(ori, light.pos);

            Ray shadowRay = Ray(ori, dir);
            shadowRay.glitchForward();


            if(rayCast.castNewRay(shadowRay, scene)) {
                if (rayCast.distanceToIntersection < lightDistance) {
                    continue;
                }
            }
            shittyLightThing += 1.f;
        }
        Color materialColor = rayCast.frontObject->getMaterial().color;
        materialColor.r *= shittyLightThing / float(scene->getLightSources().size());
        materialColor.g *= shittyLightThing / float(scene->getLightSources().size());
        materialColor.b *= shittyLightThing / float(scene->getLightSources().size());
        return materialColor;
    }
    return scene->getBackgroundColor();
}

void drawScene()
{
    auto start = std::chrono::high_resolution_clock::now();
    for (int y = 0; y < RES_Y; y++)
    {
        for (int x = 0; x < RES_X; x++)
        {
            // if(MojaveWorkAround){
            //   glutReshapeWindow(2 * RES_X,2 * RES_Y);//Necessary for Mojave. Has to be different dimensions than in glutInitWindowSize();
            //   // MojaveWorkAround = false;
            // }
            Ray ray = scene->getCamera()->getPrimaryRay(x, y);
            Color color = rayTracing(ray, 1, 1.0f); //depth=1, ior=1.0
            glBegin(GL_POINTS);
            glColor3f(color.r, color.g, color.b);
            //glColor3f(1.0f, 0, 0);
            glVertex2f(x, y);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    cout << "Rendering computation time: " << diff.count() << " s\n";

    glEnd();
    glFlush();
    printf("Terminated!\n");

    if(MojaveWorkAround){
      glutReshapeWindow(0.99 * RES_X,0.99 * RES_Y);//Necessary for Mojave. Has to be different dimensions than in glutInitWindowSize();
      // MojaveWorkAround = false;
    }
}


int main(int argc, char**argv)
{

    scene = new Scene();
    if(!(scene->load_nff("./scenes/balls_low.nff"))) {
        return 0;
    }
    std::cout << "test intersect" << std::endl;
    Ray ray(Vector(0.3, 0.3, 0.6), Vector(0, 0.1f, -0.1f));
    Material mat;
    Object *sphere = new Sphere(Vector(0.3,0.3,0.5), 0.2f, mat);
    sphere->intersect(ray);
    Vector intersection(vectorAdd(ray.ori, vectorScale(ray.dir, ray.t)));
    vectorPrint(intersection);

    RES_X = scene->getCamera()->ResX;
    RES_Y = scene->getCamera()->ResY;
    scene->getCamera()->printCameraSetup();
    //printf("resx = %dresy= %d.\n", RES_X, RES_Y);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(RES_X, RES_Y);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Group 14: Ray Tracing");
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glutReshapeFunc(reshape);
    glutDisplayFunc(drawScene);
    glDisable(GL_DEPTH_TEST);
    // std::cout << "1" << '\n';
    glutMainLoop();
    // std::cout << "0" << '\n';
    return 0;
}
