cmake_minimum_required(VERSION 3.13)
project(project)

set(CMAKE_CXX_STANDARD 17)

add_executable(project main.cpp Scene.h Scene.cpp Camera.cpp Camera.h Object.cpp Object.h Sphere.cpp Sphere.h Plane.cpp Plane.h VectorMath.cpp Triangle.cpp Triangle.h Cylinder.h RayCast.cpp RayCast.h RandomSampler.cpp RandomSampler.h Grid.cpp Grid.h Cell.cpp Cell.h AABB.h AABB.cpp testVector.cpp Vector.cpp Vector.h)

