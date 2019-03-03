#include <stdlib.h>
// #include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include "Scene.h"
// g++ main.cpp Scene.cpp Camera.cpp Object.cpp Sphere.cpp Plane.cpp -o app -lglut -lGLU -lGL
// ... -lGLEW

#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>


#define MAX_DEPTH 6

Scene* scene = NULL;
int RES_X, RES_Y;

// bool MojaveWorkAround = 1;

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
Color rayTracing(Ray ray, int depth, int indexOfRefraction) {
    //TODO


}

void drawScene()
{
    for (int y = 0; y < RES_Y; y++)
    {
        for (int x = 0; x < RES_X; x++)
        {
          // if(MojaveWorkAround){
          //   glutReshapeWindow(2 * RES_X,2 * RES_Y);//Necessary for Mojave. Has to be different dimensions than in glutInitWindowSize();
          //   // MojaveWorkAround = false;
          // }
            Ray ray = scene->getCamera()->PrimaryRay(x, y);
            Color color=rayTracing(ray, 1, 1.0 ); //depth=1, ior=1.0
            glBegin(GL_POINTS);
            //glColor3f(color.r(), color.g(), color.b());
            glColor3f(1.0f, 0, 0);
            glVertex2f(x, y);
            glEnd();
            glFlush();
        }
    }
    printf("Terminated!\n");
    // if(MojaveWorkAround){
    //   glutReshapeWindow(2 * RES_X,2 * RES_Y);//Necessary for Mojave. Has to be different dimensions than in glutInitWindowSize();
    //   // MojaveWorkAround = false;
    // }
}


int main(int argc, char**argv)
{

    scene = new Scene();
    if(!(scene->load_nff("./scenes/balls_low.nff"))) {
        return 0;
    }

    RES_X = 512; //scene->GetCamera()->GetResX();
    RES_Y = 512; //scene->GetCamera()->GetResY();
    printf("resx = %dresy= %d.\n", RES_X, RES_Y);
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
