#include "Shape.h"
#include "variables.h"
#include <Windows.h>
#include <stdio.h>
#include <tchar.h> 

#define DP1(fmt,var) {TCHAR sOut[256];_stprintf_s(sOut,_T(fmt),var);OutputDebugString(sOut);} 

Sphere::Sphere() : radius(0),center(0,0,0){
	
}
Sphere::Sphere(float r, Point &center){
	this->radius = r;
	this->center = center;
}
Sphere::~Sphere(){
	
}
bool Sphere::intersect(Ray& ray, float* thit, LocalGeo* local){
	bool hasAnswer = intersectP(ray);
	Ray rayt = ray;
	rayt.pos = (mat).inverse().transform(rayt.pos);
	rayt.dir = (mat).inverse().transformD(rayt.dir);
	if (hasAnswer)
	{
		Vector3 d = rayt.dir;
		Vector3 ec = Vector3((rayt.pos - center));
		float criterion = d.dot(ec)*d.dot(ec) - d.dot(d)*(ec.dot(ec) - radius*radius);
		float t = (-d.dot(ec)-sqrt(criterion))/d.dot(d);
		local->pos = rayt.pos + rayt.dir*t;
		Vector3 tempNormal = Vector3((local->pos - center) * 2).normalize();
		local->normal = Normal(mat.inverse().transposition().transform(tempNormal));
		if ((Vector3(eye[0], eye[1], eye[2]) - local->pos).dot(local->normal) < 0)
		{
			local->normal = Normal(-local->normal.x, -local->normal.y, -local->normal.z);
		}
		if (t<ray.t_min || t>ray.t_max)
		{
			return false;
		}
		local->t = t;
		return true;
	}
	else
	{
		return false;
	}
}
bool Sphere::intersectP(Ray& ray){
	Ray rayt = ray;
	rayt.pos = (mat).inverse().transform(rayt.pos);
	rayt.dir = (mat).inverse().transformD(rayt.dir);
	Vector3 d = rayt.dir;
	Vector3 ec = Vector3((rayt.pos - center));
	float result = d.dot(ec)*d.dot(ec)-d.dot(d)*(ec.dot(ec)-radius*radius);
	if (result >= 0)
		return true;
	else
		return false;
}

BBox Sphere::getBoundingBox()
{
	return BBox(
		mat.transform(Vector3(center.x - radius,center.y - radius,center.z -radius)),
		mat.transform(Vector3(center.x + radius,center.y + radius,center.z + radius)));
}

Vector3 Sphere::getMidPoint()
{
	return center;
}

bool Triangle::intersect(Ray& ray, float* thit, LocalGeo* local){
	Vector3 e1 = p1 - p0;
	Vector3 e2 = p2 - p0;
	Vector3 p = ray.dir.cross(e2);
	float det = e1.dot(p);
	Vector3 t;
	if (det > 0)
	{
		t = Vector3(ray.pos) - p0;
	}
	else
	{
		t = p0 - Vector3(ray.pos);
		det = -det;
	}
	if (det < 0.0001f)
	{
		return false;
	}
	float u = t.dot(p);
	if (u < 0.0f || u >det)
	{
		return false;
	}
	Vector3 q = t.cross(e1);
	float v = ray.dir.dot(q);
	if (v < 0.0f || u+v>det)
	{
		return false;
	}
	float T = e2.dot(q);
	float fInvDet = 1.0f / det;
	T *= fInvDet;
	local->pos = ray.pos + ray.dir*T;
	if ((Vector3(eye[0], eye[1], eye[2]) - local->pos).dot(normal) < 0)
	{
		local->normal = Normal(-normal.x,-normal.y,-normal.z);
	}
	local->t = T;
//	DP1("%f\n",T);
	return true;
}
bool Triangle::intersectP(Ray& ray){
	float hi;
	LocalGeo l;
	return intersect(ray,&hi,&l);
}

BBox Triangle::getBoundingBox()
{
	Vector3 bottom(
		std::fminf(std::fminf(p0.x,p1.x),p2.x),
		std::fminf(std::fminf(p0.y, p1.y), p2.y),
		std::fminf(std::fminf(p0.z, p1.z), p2.z)
		);
	Vector3 tail(
		std::fmaxf(std::fmaxf(p0.x,p1.x),p2.x),
		std::fmaxf(std::fmaxf(p0.y, p1.y), p2.y),
		std::fmaxf(std::fmaxf(p0.z, p1.z), p2.z)
	);
	return BBox(bottom,tail);
}

Vector3 Triangle::getMidPoint()
{
	return Vector3(
		(p0.x + p1.x + p2.x) / 3.0,
		(p0.y + p1.y + p2.y) / 3.0,
		(p0.z + p1.z + p2.z) / 3.0
	);
}

bool Box::intersect(Ray& ray, float* thit, LocalGeo* local){
	return false;
}
bool Box::intersectP(Ray& ray){
	return false;
}
void Box::trans(Matrix& matrix){

}

bool Disk::intersect(Ray& ray, float* thit, LocalGeo* local){
	return false;
}
bool Disk::intersectP(Ray& ray){
	return false;
}
void Disk::trans(Matrix& matrix){
}

bool Rectangle::intersect(Ray& ray, float* thit, LocalGeo* local){
	return false;
}
bool Rectangle::intersectP(Ray& ray){
	return false;
}
void Rectangle::trans(Matrix& matrix){

}

bool Cylinder::intersect(Ray& ray, float* thit, LocalGeo* local){
	return false;
}
bool Cylinder::intersectP(Ray& ray){
	return false;
}
void Cylinder::trans(Matrix& matrix){

}

bool Torus::intersect(Ray& ray, float* thit, LocalGeo* local){
	return false;
}
bool Torus::intersectP(Ray& ray){
	return false;
}
void Torus::trans(Matrix& matrix){

}
