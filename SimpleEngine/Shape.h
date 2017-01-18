#ifndef SHAPE_H_
#define SHAPE_H_
#include"Ray.h"
#include "vector.h"
#include "matrix.h"
class Shape
{
public:
	virtual bool intersect(Ray& ray, float* thit, LocalGeo* local)=0;
	virtual bool intersectP(Ray& ray)=0;
	virtual void trans(Matrix& matrix)=0;
private:

};

class Sphere : public Shape{	
public:
	Sphere();
	Sphere(float r,Point &center);
	~Sphere();
	bool intersect(Ray& ray, float* thit, LocalGeo* local) ;
	bool intersectP(Ray& ray) ;
	void trans(Matrix& matrix){
		this->mat = matrix;
	}
public:
	float radius;
	Point center;
	Matrix mat;
};

class Triangle : public Shape{
public:
	Triangle(){}
	Triangle(Vector3 &t1,Vector3 &t2,Vector3 &t3){
		this->p0 = t1;
		this->p1 = t2;
		this->p2 = t3;
		normal = (p2 - p0).cross(p1-p0);
	}
	bool intersect(Ray& ray, float* thit, LocalGeo* local);
	bool intersectP(Ray& ray);
	void trans(Matrix& matrix){
		this->p0 = matrix.transform(p0);
		this->p1 = matrix.transform(p1);
		this->p2 = matrix.transform(p2);
		this->normal = (p2 - p0).cross(p1 - p0);
	}
	~Triangle(){}
public:
	Vector3 p0, p1, p2;
	Vector3 normal;
};

#endif