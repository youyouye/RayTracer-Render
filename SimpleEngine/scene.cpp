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
#include <functional>
#include <memory>
#include <thread>

std::function<void(int, int, double,double,double)> Scene::pixmap_callback_;

void Scene::render(int samples){
	width_ = 1280;
	height_ = 720;
	RayTracer raytrace;
	Camera camera;
//	readUserDefinedFile(raytrace, camera);
	testObjectModel(raytrace,camera);
	raytrace.generateKDTree();

	Sampler sample =Sampler(width_,height_);
	Film film(width_,height_);
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

void Scene::thread_render(int samples)
{
	LOG_INFO << "start!" << LOG_END;
//	width_ = 1280;
//	height_ = 720;
	width_ = 1080;
	height_ = 1080;
	samples = sample_;
	Film film(width_, height_);
	film.SetCommitCallback(pixmap_callback_);
	const int thread_num = 6;
	std::thread threads[thread_num];
	for (int i = 0; i < thread_num; i++)
	{
		auto func = [i, samples, &film](){
			render_task(i, samples, film);
		};
		threads[i] = std::thread(func);
	}
	for (auto& t : threads)
	{
		t.join();
	}
	film.writeImage();
	end_callback_();
	LOG_INFO << "end!" << LOG_END;
}

void Scene::render_task(int n, int samples, Film& film)
{
	RayTracer raytrace;
	Camera camera;
	if (module_type_)
	{
		testObjectModel(raytrace, camera);
	}
	else 
	{
		readUserDefinedFile(raytrace, camera);
	}
	raytrace.generateKDTree();
	Sampler sample = Sampler(width_, height_);
	Sample sam;
	while (sample.getThreadSample(n,sam))
	{
		sample.getExecPercent();
		Ray ray;
		Color cr;
		for (int a = 0; a < samples; a++)
		{
			unsigned short X[3] = { 0,0,sam.y*sam.y*sam.x };
			camera.generateRay(sam, &ray, a > 0, X);
			Color temp_cr;
			raytrace.kd_trace(ray, 0, temp_cr, X);
			cr = cr + temp_cr;
		}
		cr = cr*(1.0 / samples);
		//		raytrace.trace(ray, 1,cr);
		film.commit(sam, cr * 255);
	}
	float how = raytrace.thit;
}

//we read camera param,shape param,light param
void Scene::readUserDefinedFile(RayTracer& raytrace, Camera& camera)
{
	ReadFile variables;
	variables.readfile(setting_filename_.c_str());
	camera = Camera(Vector3(variables.camera[0], variables.camera[1], variables.camera[2]), Vector3(variables.camera[3], variables.camera[4], variables.camera[5]), Vector3(variables.camera[6], variables.camera[7], variables.camera[8]), variables.camera[9],width_,height_);
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
	camera = Camera(Vector3(camera_param_[0],camera_param_[1],camera_param_[2]),Vector3(camera_param_[3],camera_param_[4],camera_param_[5]),
		Vector3(camera_param_[6],camera_param_[7],camera_param_[8]),camera_param_[9],width_,height_);
	auto mesh = std::make_shared<Mesh>(module_filename_);
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

void Scene::SetGloablParam(double width, double height, int sample)
{
	width_ = width;
	height_ = height;
	sample_ = sample;
}

void Scene::SetSettingFile(const std::string& file) 
{
	setting_filename_ = file;
}

void Scene::SetModuleFile(const std::string& file) 
{
	module_filename_ = file;
}

void Scene::SetCameraParam(double pox_x, double pox_y, double pox_z,
	double up_x, double up_y, double up_z,
	double target_x, double target_y, double target_z,
	int angle) 
{
	camera_param_[0] = pox_x;
	camera_param_[1] = pox_y;
	camera_param_[2] = pox_z;
	camera_param_[3] = up_x;
	camera_param_[4] = up_y;
	camera_param_[5] = up_z;
	camera_param_[6] = target_x;
	camera_param_[7] = target_y;
	camera_param_[8] = target_z;
	camera_param_[9] = angle;
}

void Scene::SetType(bool model_type)
{
	module_type_ = model_type;
}

void Scene::SetPixmapCallback(const std::function<void(int, int, double,double,double)> callback)
{
	pixmap_callback_ = callback;
}
