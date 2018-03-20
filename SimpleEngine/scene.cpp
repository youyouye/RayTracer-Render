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
#include "Shape.h"
#include <stdlib.h>
#include <iostream>
#include <memory>

void Scene::render(int samples){
	width = 1280;
	height = 720;
	RayTracer raytrace;
	Camera camera;
//	readUserDefinedFile(raytrace, camera);
	testObjectModel(raytrace,camera);
	raytrace.generateKDTree();

	Sampler sample =Sampler(width,height);
	Film film = Film(width,height);
	Sample sam;
	LOG_INFO << "k-d tree start!" << LOG_END;

	while (sample.getSample(sam))
	{
		sample.getExecPercent();
		Ray ray;		
		Color cr;
		for (int a = 0; a<samples; a++)
		{
			unsigned short X[3] = { 0,0,sam.y*sam.y*sam.x };
			camera.generateRay(sam, &ray,a>0,X);
			Color temp_cr;
			raytrace.kd_trace(ray, 0, temp_cr, X);
			cr = cr + temp_cr;
		}
		cr = cr*(1.0 / samples);
//		raytrace.trace(ray, 1,cr);
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
	camera = Camera(Vector3(variables.camera[0], variables.camera[1], variables.camera[2]), Vector3(variables.camera[3], variables.camera[4], variables.camera[5]), Vector3(variables.camera[6], variables.camera[7], variables.camera[8]), variables.camera[9],width,height);
	addObject(raytrace,variables);
//	auto bottom = std::make_shared<GeometricPrimitive>(new Sphere(1000, Point(0, 0, -1000)), new Material(DIFFUSE, Color(1, 1, 1)));
//	auto left = std::make_shared<GeometricPrimitive>(new Sphere(1000, Point(-1004, 0, 0)), new Material(DIFFUSE, Color(0.85, 0.4, 0.4)));
//	auto right = std::make_shared<GeometricPrimitive>(new Sphere(1000, Point(1004, 0, 0)), new Material(DIFFUSE, Color(0.4, 0.4, 0.85)));
//	auto top = std::make_shared<GeometricPrimitive>(new Sphere(1000, Point(0, 1006, 0)), new Material(DIFFUSE, Color(1, 1, 1)));
//	auto emit_light = std::make_shared<GeometricPrimitive>(new Sphere(100, Point(0, 0, 110)), new Material(EMIT, Color(2.2, 2.2, 2.2)));
//	addSingleObject(raytrace, bottom);
//	addSingleObject(raytrace, left);
//	addSingleObject(raytrace, right);
//	addSingleObject(raytrace, top);
//	addSingleObject(raytrace, emit_light);
}

void Scene::testObjectModel(RayTracer& raytrace, Camera& camera)
{
	camera = Camera(Vector3(0,-5,2.5),Vector3(0,0,1),Vector3(0,-5,5),60,width,height);
	auto mesh = std::make_shared<Mesh>("..//model//dragon2.obj");
	addObject(raytrace, *mesh);

	auto bottom = std::make_shared<GeometricPrimitive>(new Sphere(1000,Point(0,0,-1000)),new Material(DIFFUSE,Color(1,1,1)));
	auto left = std::make_shared<GeometricPrimitive>(new Sphere(1000, Point(-1004, 0, 0)), new Material(DIFFUSE,Color(0.85,0.4,0.4)));
	auto right = std::make_shared<GeometricPrimitive>(new Sphere(1000, Point(1004, 0, 0)), new Material(DIFFUSE,Color(0.4, 0.4, 0.85)));
	auto top = std::make_shared<GeometricPrimitive>(new Sphere(1000, Point(0, 1006, 0)), new Material(DIFFUSE, Color(1, 1, 1)));
	auto emit_light = std::make_shared<GeometricPrimitive>(new Sphere(100, Point(0, 0, 110)), new Material(EMIT,Color(2.2,2.2,2.2)));
	addSingleObject(raytrace, bottom);
	addSingleObject(raytrace, left);
	addSingleObject(raytrace, right);
	addSingleObject(raytrace, top);
	addSingleObject(raytrace, emit_light);
}

void Scene::addSingleObject(RayTracer& raytrace, std::shared_ptr<Primitive> primitive)
{
	raytrace.primitives.push_back(primitive);
}