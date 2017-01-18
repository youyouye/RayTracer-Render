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
		local->pos = mat.transform(Vector3(ray.pos + ray.dir*t));
		Vector3 tempNormal = (local->pos - center) * 2;
		local->normal = Normal(mat.inverse().transposition().transform(tempNormal));
		if (t<ray.t_min)
		{
			return false;
		}
		local->t = (local->pos-ray.pos).length();
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
	local->normal = normal;
	local->t = T;
//	DP1("%f\n",T);
	return true;
}
bool Triangle::intersectP(Ray& ray){
	float hi;
	LocalGeo l;
	return intersect(ray,&hi,&l);
}
