cmake_minimum_required(VERSION 2.6)

project (RayTrace C CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CXX_FLAGS
    -g
    -Wall
   )

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -finline-limit=1000 -DNDEBUG -std=c++11 -Wno-narrowing -fpermissive" )
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -finline-limit=1000 -DNDEBUG -std=c++11 -Wno-narrowing -fpermissive")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

   # add the binary tree to the search path for include files
include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})

message(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

set(SOURCE_FILES
    SimpleEngine/main.cpp
    SimpleEngine/BBox.cpp
    SimpleEngine/BRDF.cpp
    SimpleEngine/camera.cpp
    SimpleEngine/canvas.cpp
    SimpleEngine/color.cpp
    SimpleEngine/film.cpp
    SimpleEngine/image.cpp
    SimpleEngine/kdtree.cpp
    SimpleEngine/light.cpp
    SimpleEngine/Log.cpp
    SimpleEngine/material.cpp
    SimpleEngine/matrix.cpp
    SimpleEngine/mesh.cpp
    SimpleEngine/PathTracer.cpp
    SimpleEngine/Point.cpp
    SimpleEngine/Primitive.cpp
    SimpleEngine/Ray.cpp
    SimpleEngine/RayTracer.cpp
    SimpleEngine/readfile.cpp
    SimpleEngine/sampler.cpp
    SimpleEngine/scene.cpp
    SimpleEngine/Shape.cpp
    SimpleEngine/small_test.cpp
    SimpleEngine/texture.cpp
    SimpleEngine/variables.cpp
    SimpleEngine/vector.cpp
    SimpleEngine/vertex.cpp
    SimpleEngine/rand48/rand48.c
    SimpleEngine/tiny_obj_loader/tiny_obj_loader.cc
)
add_executable(raytrace ${SOURCE_FILES})
target_link_libraries(raytrace freeimage)

