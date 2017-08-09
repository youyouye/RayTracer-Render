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
class BBox;
class Primitive
{
public:
	virtual bool interset(Ray& ray,float* thit,Intersection* in) = 0;
	virtual bool intersectP(Ray& ray) = 0;
	virtual BRDF* getBRDF(LocalGeo& local) { return nullptr; }
	virtual BBox getBoundingBox();
	virtual Vector3 getSpecialVec();
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
	virtual BRDF* getBRDF(LocalGeo& local);
	virtual Vector3 getSpecialVec();
public:
	Shape* shape;
	Material* mat;
	Matrix trans;
};

class AggregatePrimitive : public Primitive{
public:
	AggregatePrimitive();
	~AggregatePrimitive();
	virtual bool interset(Ray& ray, float* thit, Intersection* in);
	virtual bool intersectP(Ray& ray);
	virtual BRDF* getBRDF(LocalGeo& local);

	inline int getNumOfObjects(){
		return objects.size();
	}
	void setMaterial(const Material& marptr);
	void addObject(const std::shared_ptr<Primitive> shapeptr);
protected:
	std::vector<std::shared_ptr<Primitive>> objects;
};

#endif