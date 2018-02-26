#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include "vector.h"
#include "BRDF.h"
#include "Shape.h"
#include "matrix.h"
#include <vector>
#include <memory>
class Ray;
class Intersection;
class Material;
class Primitive
{
public:
	virtual bool interset(Ray& ray,float* thit,Intersection* in) = 0;
	virtual bool intersectP(Ray& ray) = 0;
	virtual void getBRDF(LocalGeo& local,BRDF* brdf) = 0;
	virtual BBox getBoundingBox() const { return BBox(); }
	virtual Vector3 getMidPoint() const { return Vector3(); }
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
	BBox getBoundingBox() const override;
	Vector3 getMidPoint() const override;
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

	void setMaterial(const Material& marptr);
	void addObject(const std::shared_ptr<Shape> shapeptr);
private:
	std::vector<std::shared_ptr<Shape>> objects;
};

#endif