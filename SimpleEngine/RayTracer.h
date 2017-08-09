#ifndef RAYTRACER_H_
#define RAYTRACER_H_
#include "Ray.h"
#include "color.h"
#include "Shape.h"
#include "Primitive.h"
#include "light.h"
#include <vector>
#include <memory>
class RayTracer{
public:
	RayTracer(){}
	RayTracer(Shape& shape) : thit(0){
		this->shape = &shape;
	};
	RayTracer(Primitive* p) :thit(0){
		this->primitive = p;
	};
	void trace(Ray& ray,int depth,Color& color);
	Color* shading(LocalGeo local, BRDF brdf, Ray lray, Color lcolor);
	void createReflectRay(LocalGeo local,Ray& ray);
	bool interset(Ray& ray, float* thit, Intersection* in);
	bool intersectP(Ray &ray);
public:
	Vector3 eye;
	Shape* shape;
	Primitive* primitive;
	std::vector<std::shared_ptr<Primitive>> primitives;
	float thit;
	std::vector<std::shared_ptr<Light>> lights;
};

#endif