#include "MeshTriangle.h"
#include "MeshTriangle.h"
#include <algorithm>

MeshTriangle::MeshTriangle()
	:Primitive(),
	mesh_ptr(nullptr),
	index0(0), index1(0), index2(0),
	normal()
{
}

MeshTriangle::MeshTriangle(Mesh* _mesh_ptr, const int i1, const int i2, const int i3)
	:Primitive(),
	mesh_ptr(_mesh_ptr),
	index0(i1), index1(i2), index2(i3)
{
}

MeshTriangle::~MeshTriangle()
{
	if (mesh_ptr)
	{
		delete mesh_ptr;
		mesh_ptr = nullptr;
	}
}

MeshTriangle::MeshTriangle(const MeshTriangle& mt)
	:Primitive(mt),
	mesh_ptr(mt.mesh_ptr),
	index0(mt.index0), index1(mt.index1), index2(mt.index2),
	normal(mt.normal)
{
}
MeshTriangle& MeshTriangle::operator= (const MeshTriangle& rhs){
	if (this == &rhs)
	{
		return (*this);
	}
	Primitive::operator=(rhs);
	mesh_ptr = rhs.mesh_ptr;
	index0 = rhs.index0;
	index1 = rhs.index1;
	index2 = rhs.index2;
	normal = rhs.normal;
	return (*this);
}

bool MeshTriangle::interset(Ray& ray, float* thit, Intersection* in){
	
}
bool MeshTriangle::intersectP(Ray& ray){
	
}
Normal MeshTriangle::getNormal() const{
	return (normal);
}
void MeshTriangle::computeNormal(const bool reverseNormal){
	//ÔÝ´ý.
}
BBox MeshTriangle::getBoundingBox(){
	float delta = 0.0001;
	Vector3 v1(mesh_ptr->vertices[index0]);
	Vector3 v2(mesh_ptr->vertices[index1]);
	Vector3 v3(mesh_ptr->vertices[index2]);
	return (BBox(min(min(v1.x, v2.x), v3.x) - delta, max(max(v1.x, v2.x), v3.x) + delta,
		min(min(v1.y, v2.y), v3.y) - delta, max(max(v1.y, v2.y), v3.y) + delta,
		min(min(v1.z, v2.z), v3.z) - delta, max(max(v1.z, v2.z), v3.z) + delta));
}
float MeshTriangle::interpolate_u(const float beta, const float gamma) const{
	return ((1 - beta - gamma) * mesh_ptr->u[index0]
		+ beta * mesh_ptr->u[index1]
		+ gamma * mesh_ptr->u[index2]);
}
float MeshTriangle::interpolate_v(const float beta, const float gamma) const{
	return ((1 - beta - gamma) * mesh_ptr->v[index0]
		+ beta * mesh_ptr->v[index1]
		+ gamma * mesh_ptr->v[index2]);
}