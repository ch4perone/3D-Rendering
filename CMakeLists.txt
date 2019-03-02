cmake_minimum_required(VERSION 3.13)
project(project)

set(CMAKE_CXX_STANDARD 14)

add_executable(project main_V2.cpp Scene.h Scene.cpp Camera.cpp Camera.h Object.cpp Object.h Sphere.cpp Sphere.h Plane.cpp Plane.h)
