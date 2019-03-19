# 3D-Rendering

Project done by Group 14 (Yannek Nowatzky and Ferdous Nasri)

## How to run the program:
### Using Linux:
The program is ready to run on linux system with the following command:
`g++ main.cpp Scene.cpp Camera.cpp Object.cpp Sphere.cpp Plane.cpp Triangle.cpp VectorMath.cpp RayCast.cpp Cylinder.cpp -o app -lglut -lGLU -lGL`

### Using MacOS Mojave:
If you are running the program on MacOS Mojave, please look in the `main.cpp` file and set `MojaveWorkAround` to `true` and uncomment the three lined with the `#include` files, while commenting out the `#include` file listed under `For Linux`. You can then run the program using the following command:
`g++ main.cpp Scene.cpp Camera.cpp Object.cpp Sphere.cpp Plane.cpp Triangle.cpp VectorMath.cpp RayCast.cpp Cylinder.cpp -o app -framework OpenGL -framework GLUT -Wno-deprecated`

## Multi-threading:
We have implemented ways to parallelize the ray tracing algorithm. This decreases the run-time drastically for the high definition pictures. To use this, you can run the commands as before and add the tag `-fopenmp`. By default, all cores will be used. If need be, this can be changed by uncommenting a line in the `main.cpp`.

## Set input file:
We currently only accept NFF. You can change the input file in `main.cpp` by changing `scene_path`.
