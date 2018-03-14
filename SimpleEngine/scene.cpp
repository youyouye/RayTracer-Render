#include "scene.h"
#include "sampler.h"
#include "variables.h"
#include "film.h"
#include "camera.h"
#include "Shape.h"
#include "material.h"
#include "readfile.h"
#include "mesh.h"
#include "Log.h"
#include <stdlib.h>
#include <iostream>
#include <memory>

void Scene::render(){
	Sampler sample =Sampler(width,height);
	Film film = Film(width,height);
	Sample sam;
	Ray ray;
	RayTracer raytrace;
	Camera camera;
//	readUserDefinedFile(raytrace, camera);
	testObjectModel(raytrace,camera);
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

//we read camera param,shape param,light param
void Scene::readUserDefinedFile(RayTracer& raytrace, Camera& camera)
{
	ReadFile variables;
	variables.readfile("..//model//scene7.test");
	camera = Camera(Vector3(variables.camera[0], variables.camera[1], variables.camera[2]), Vector3(variables.camera[3], variables.camera[4], variables.camera[5]), Vector3(variables.camera[6], variables.camera[7], variables.camera[8]), variables.camera[9]);
	addObject(raytrace,variables);
}

void Scene::testObjectModel(RayTracer& raytrace, Camera& camera)
{
	camera = Camera(Vector3(0,-5,2.5),Vector3(0,0,1),Vector3(0,0,1),60);
	auto mesh = std::make_shared<Mesh>("..//model//dragon2.obj");
	addObject(raytrace, *mesh);
}