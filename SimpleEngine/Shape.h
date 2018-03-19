#ifndef SHAPE_H_
#define SHAPE_H_
#include"Ray.h"
#include "vector.h"
#include "matrix.h"
#include "BBox.h"
class Shape
{
public:
	virtual bool intersect(Ray& ray, float* thit, float& tmin, LocalGeo* local)=0;
	virtual bool intersectP(Ray& ray)=0;
	virtual void trans(Matrix& matrix)=0;
	virtual BBox getBoundingBox() { return BBox(); }
	virtual Vector3 getMidPoint() { return Vector3(); }
	virtual void GetTexturePosition(const Vector3& point,float& u,float& v) {}
private:

};

class Sphere : public Shape{	
public:
	Sphere();
	Sphere(float r,Point center);
	~Sphere();
	bool intersect(Ray& ray, float* thit,float& tmin, LocalGeo* local) override;
	bool intersectP(Ray& ray) ;
	void trans(Matrix& matrix){
		this->mat = matrix;
	}
	BBox getBoundingBox() override;
	Vector3 getMidPoint() override;
	void GetTexturePosition(const Vector3& point,float& u, float& v) override;
public:
	float radius;
	Point center;
	Matrix mat;
};

class Triangle : public Shape{
public:
	Triangle(){}
	Triangle(Vector3 &t1,Vector3 &t2,Vector3 &t3){
		this->p0_ = t1;
		this->p1_ = t2;
		this->p2_ = t3;
		normal = (p2_ - p0_).cross(p1_-p0_).normalize();
	}
	
	Triangle(Vector3 &p0, Vector3 &p1, Vector3 &p2,
		Vector3 &t0,Vector3& t1,Vector3& t2) 
		:p0_(p0),p1_(p1),p2_(p2),t0_(t0),t1_(t1),t2_(t2)
	{
		normal = (p2_ - p0_).cross(p1_ - p0_).normalize();
	}
	~Triangle() {}

	bool intersect(Ray& ray, float* thit, float& tmin, LocalGeo* local) override;
	bool intersectP(Ray& ray);
	void trans(Matrix& matrix){
		this->p0_ = matrix.transform(p0_);
		this->p1_ = matrix.transform(p1_);
		this->p2_ = matrix.transform(p2_);
		this->normal = (p2_ - p0_).cross(p1_ - p0_).normalize();
	}
	BBox getBoundingBox() override;
	Vector3 getMidPoint() override;
	void GetTexturePosition(const Vector3& point,float& u, float& v) override;
public:
	Vector3 p0_, p1_, p2_;
	Vector3 t0_, t1_, t2_;		//texture coordinates
	Vector3 normal;
private:
	Vector3 getBarycentric(const Vector3& point);
};

class Box : public Shape{
public:
	Box() = default;
	~Box() = default;
public:
	Normal getNormal(const int face_hit) const {
		switch (face_hit)
		{
		case 0: return Normal(-1,0,0); //-x
		case 1: return Normal(0, -1, 0); //-y
		case 2: return Normal(0, 0, -1); //-z
		case 3: return Normal(1, 0, 0); //x
		case 4: return Normal(0, 1, 0); //y
		case 5: return Normal(0,0,1); //z
		}
	}
	virtual bool intersect(Ray& ray, float* thit, float& tmin, LocalGeo* local) override;
	virtual bool intersectP(Ray& ray);
	virtual void trans(Matrix& matrix);
};

class Disk :public Shape{
public:
	Disk() = default;
	~Disk() = default;
public:
	virtual bool intersect(Ray& ray, float* thit,float& tmin, LocalGeo* local) override;
	virtual bool intersectP(Ray& ray);
	virtual void trans(Matrix& matrix);
};

class Rectangle :public Shape{
public:
	Rectangle() = default;
	~Rectangle() = default;
public:
	virtual bool intersect(Ray& ray, float* thit, float& tmin, LocalGeo* local) override;
	virtual bool intersectP(Ray& ray);
	virtual void trans(Matrix& matrix);
};

class Cylinder :public Shape{
public:
	Cylinder() = default;
	~Cylinder() = default;
public:
	virtual bool intersect(Ray& ray, float* thit, float& tmin, LocalGeo* local) override;
	virtual bool intersectP(Ray& ray);
	virtual void trans(Matrix& matrix);
};

class Torus :public Shape{
public:
	Torus();
	~Torus();
public:
	virtual bool intersect(Ray& ray, float* thit, float& tmin, LocalGeo* local) override;
	virtual bool intersectP(Ray& ray);
	virtual void trans(Matrix& matrix);
};




#endif
