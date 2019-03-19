#include <stdlib.h>
// #include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <cassert>
#include "Scene.h"
#include "RayCast.h"
#include "VectorMath.cpp"
// g++ main.cpp Scene.cpp Camera.cpp Object.cpp Sphere.cpp Plane.cpp Triangle.cpp VectorMath.cpp RayCast.cpp Cylinder.cpp -o app -framework OpenGL -framework GLUT -Wno-deprecated
// g++ main.cpp Scene.cpp Camera.cpp Object.cpp Sphere.cpp Plane.cpp Triangle.cpp VectorMath.cpp RayCast.cpp Cylinder.cpp -o app -lglut -lGLU -lGL
// ... -lGLEW

#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>


#define MAX_DEPTH 4

Scene* scene = NULL;
string scene_path = "./scenes/balls_cylinder.nff";
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
        Object *frontObject = rayCast.frontObject;
        Vector intersectionPoint = rayCast.intersectionPoint;
        vector<Light> activeLights;
        for (Light &light : scene->getLightSources()) {
            Vector dir = vectorDirection(intersectionPoint, light.pos);
            float lightDistance = vectorDistance(intersectionPoint, light.pos);

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

            Color reflectedColor = rayTracing(reflectedRay, depth + 1, indexOfRefraction);
            reflectedColor.scale(frontObject->getMaterial().specularComponent);
            color.addColor(reflectedColor);
        }

        //Refraction
        if(frontObject->isTranslucid()) {
            Vector v = vectorNormalize(vectorDirection(intersectionPoint, ray.ori));
            Vector normal = frontObject->getNormalInPoint(intersectionPoint);

            if (ray.interiorMedium) {
                normal = vectorScale(normal, -1.f);
            }

            Vector v_t = vectorSubstract(vectorScale(normal, vectorDotProduct(v, normal)), v);

            float sinTeta_i = vectorLength(v_t);
            float sinTeta_t = (indexOfRefraction / frontObject->getMaterial().indexOfRefraction) * sinTeta_i;

            if(abs(sinTeta_t) > 1.f) {
                cout << "ERROR: sin teta t > 1, infact is: " << sinTeta_t << endl;
                abort();
                return Color(0,0,0);
            }
            float cosTeta_t = sqrt(1 - sinTeta_t * sinTeta_t);

            Vector t = vectorNormalize(v_t);
            Vector R = vectorAdd(vectorScale(t, sinTeta_t), vectorScale(normal, -1.f * cosTeta_t));

            Ray refractedRay(intersectionPoint, R);
            refractedRay.glitchForward();
            refractedRay.interiorMedium = !ray.interiorMedium;

            Color refractionColor = rayTracing(refractedRay, depth + 1, frontObject->getMaterial().indexOfRefraction);
            refractionColor.scale(frontObject->getMaterial().transmittance);
            color.addColor(refractionColor);
        }

        return color;
    }

    return scene->getBackgroundColor();
}

void drawScene()
{
    auto start = std::chrono::high_resolution_clock::now();

    //#pragma omp parallel for
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
    if(!(scene->load_nff(scene_path))) {
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
