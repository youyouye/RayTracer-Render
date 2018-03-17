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
bool Sphere::intersect(Ray& ray, float* thit,float& tmin, LocalGeo* local){
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
	bool has_matrix = false;
	for (int i = 0;i < 16;i++)
	{
		if (mat.p[i] != 0) has_matrix = true;
	}
	if (has_matrix)
	{
		return BBox(
			mat.transform(Vector3(center.x - radius, center.y - radius, center.z - radius)),
			mat.transform(Vector3(center.x + radius, center.y + radius, center.z + radius)));
	}
	else 
	{
		return BBox(
			Vector3(center.x - radius, center.y - radius, center.z - radius),
			Vector3(center.x + radius, center.y + radius, center.z + radius));
	}
}

Vector3 Sphere::getMidPoint()
{
	return center;
}

void Sphere::GetTexturePosition(const Vector3& point,float& u, float& v)
{

}

bool Triangle::intersect(Ray& ray, float* thit, float& tmin, LocalGeo* local){
	Vector3 e1 = p1_ - p0_;
	Vector3 e2 = p2_ - p0_;
	Vector3 p = ray.dir.cross(e2);
	float det = e1.dot(p);
	Vector3 t;
	if (det > 0)
	{
		t = Vector3(ray.pos) - p0_;
	}
	else
	{
		t = p0_ - Vector3(ray.pos);
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
	local->normal = normal;		//is so strange for not has this
	if ((Vector3(eye[0], eye[1], eye[2]) - local->pos).dot(normal) < 0)
	{
		local->normal = Normal(-normal.x,-normal.y,-normal.z);
	}
	local->t = T;
	tmin = T;
//	DP1("%f\n",T);
	return true;
}
bool Triangle::intersectP(Ray& ray){
	float hi;
	float tmin;
	LocalGeo l;
	return intersect(ray,&hi,tmin,&l);
}

BBox Triangle::getBoundingBox()
{
	Vector3 bottom(
		std::fminf(std::fminf(p0_.x,p1_.x),p2_.x),
		std::fminf(std::fminf(p0_.y, p1_.y), p2_.y),
		std::fminf(std::fminf(p0_.z, p1_.z), p2_.z)
		);
	Vector3 tail(
		std::fmaxf(std::fmaxf(p0_.x,p1_.x),p2_.x),
		std::fmaxf(std::fmaxf(p0_.y, p1_.y), p2_.y),
		std::fmaxf(std::fmaxf(p0_.z, p1_.z), p2_.z)
	);
	return BBox(bottom,tail);
}

Vector3 Triangle::getMidPoint()
{
	return Vector3(
		(p0_.x + p1_.x + p2_.x) / 3.0,
		(p0_.y + p1_.y + p2_.y) / 3.0,
		(p0_.z + p1_.z + p2_.z) / 3.0
	);
}

void Triangle::GetTexturePosition(const Vector3& point,float& u, float& v)
{
	Vector3 b = getBarycentric(point);
	Vector3 c = Vector3();
	c = c + (p0_*b.x);
	c = c + (p1_*b.y);
	c = c + (p2_*b.z);
	u = c.x;
	v = c.y;
}

Vector3 Triangle::getBarycentric(const Vector3& point)
{
	Vector3 v2 = point - p0_;
	Vector3 edge1 = p1_ - p0_;
	Vector3 edge2 = p2_ - p0_;
	double d00 = edge1.dot(edge1);
	double d01 = edge1.dot(edge2);
	double d11 = edge2.dot(edge2);
	double d20 = p2_.dot(edge1);
	double d21 = p2_.dot(edge2);
	double d = d00*d11 - d01*d01;
	double v = (d11*d20 - d01*d21) / d;
	double w = (d00*d21 - d01*d20) / d;
	double u = 1 - v - w;
	return Vector3(u,v,w);
}

bool Box::intersect(Ray& ray, float* thit, float& tmin,LocalGeo* local){
	return false;
}
bool Box::intersectP(Ray& ray){
	return false;
}
void Box::trans(Matrix& matrix){

}

bool Disk::intersect(Ray& ray, float* thit, float& tmin, LocalGeo* local){
	return false;
}
bool Disk::intersectP(Ray& ray){
	return false;
}
void Disk::trans(Matrix& matrix){
}

bool Rectangle::intersect(Ray& ray, float* thit, float& tmin, LocalGeo* local){
	return false;
}
bool Rectangle::intersectP(Ray& ray){
	return false;
}
void Rectangle::trans(Matrix& matrix){

}

bool Cylinder::intersect(Ray& ray, float* thit, float& tmin, LocalGeo* local){
	return false;
}
bool Cylinder::intersectP(Ray& ray){
	return false;
}
void Cylinder::trans(Matrix& matrix){

}

bool Torus::intersect(Ray& ray, float* thit, float& tmin, LocalGeo* local){
	return false;
}
bool Torus::intersectP(Ray& ray){
	return false;
}
void Torus::trans(Matrix& matrix){

}
