#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include "vector.h"
#include "BRDF.h"
#include "Shape.h"
#include "matrix.h"
class Ray;
class Intersection;
class Material;
class Primitive
{
public:
	virtual bool interset(Ray& ray,float* thit,Intersection* in) = 0;
	virtual bool intersectP(Ray& ray) = 0;
	virtual void getBRDF(LocalGeo& local,BRDF* brdf) = 0;
public:
};

class GeometricPrimitive : public Primitive
{
public:
	GeometricPrimitive();
	GeometricPrimitive(Shape* shape,Material* material){
		this->shape = shape;
		this->mat = material;
		trans.identify();
	}
	GeometricPrimitive(Shape* shape, Material* material,Matrix mat){
		this->shape = shape;
		this->mat = material;
		this->trans = mat;
		this->shape->trans(mat);
	}
	~GeometricPrimitive();
	bool interset(Ray& ray, float* thit, Intersection* in);
	bool intersectP(Ray& ray);
	void getBRDF(LocalGeo& local, BRDF* brdf);
public:
	Shape* shape;
	Material* mat;
	Matrix trans;
};

class AggregatePrimitive : public Primitive{
public:
	AggregatePrimitive();
	~AggregatePrimitive();
	bool interset(Ray& ray, float* thit, Intersection* in);
	bool intersectP(Ray& ray);
	void getBRDF(LocalGeo& local, BRDF* brdf);
};

#endif