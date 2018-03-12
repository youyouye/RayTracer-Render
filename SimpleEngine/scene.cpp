#include "scene.h"
#include "sampler.h"
#include "variables.h"
#include "film.h"
#include "camera.h"
#include "RayTracer.h"
#include "Shape.h"
#include "material.h"
#include "readfile.h"
#include "Log.h"
#include <stdlib.h>
#include <iostream>
#include <memory>
void Scene::render(){
	ReadFile variables;
	variables.readfile("..//hw3//scene7.test");
	Sampler sample =Sampler(width,height);
	Film film = Film(width,height);
	Sample sam;
	Ray ray;
	Camera camera = Camera(Vector3(variables.camera[0], variables.camera[1], variables.camera[2]), Vector3(variables.camera[3], variables.camera[4], variables.camera[5]), Vector3(variables.camera[6], variables.camera[7], variables.camera[8]),variables.camera[9]);
	RayTracer raytrace;
	raytrace.primitives = variables.primitives;
	raytrace.lights = variables.lights;
	raytrace.generateKDTree();

	LOG_INFO << "k-d tree start!" << LOG_END;

	while (sample.getSample(sam))
	{
		std::cout << sample.getExecPercent() << std::endl;
		camera.generateRay(sam,&ray);
		Color cr;
		raytrace.trace(ray,1,cr);
		film.commit(sam,cr*255);
	}
	float how = raytrace.thit;
	film.writeImage();

	LOG_INFO << "k-d tree end!" << LOG_END;
}
