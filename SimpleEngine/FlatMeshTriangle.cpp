#include "FlatMeshTriangle.h"
#include "math.h"

FlatMeshTriangle::FlatMeshTriangle()
{
}


FlatMeshTriangle::~FlatMeshTriangle()
{
}

FlatMeshTriangle::FlatMeshTriangle(Mesh* _mesh_ptr, const int i0, const int i1, const int i2)
	:MeshTriangle(_mesh_ptr,i0,i1,i2)
{
}

FlatMeshTriangle::FlatMeshTriangle(const FlatMeshTriangle& fmt)
	: MeshTriangle(fmt)
{	
}
FlatMeshTriangle& FlatMeshTriangle::operator = (const FlatMeshTriangle& rhs){
	if (this == &rhs)
		return (*this);
	MeshTriangle::operator= (rhs);
	return *this;
}

FlatMeshTriangle* FlatMeshTriangle::clone() const{
	return (new FlatMeshTriangle(*this));
}

bool FlatMeshTriangle::interset(Ray& ray, float* thit, Intersection* in){
	Vector3 v0(mesh_ptr->vertices[index0]);
	Vector3 v1(mesh_ptr->vertices[index1]);
	Vector3 v2(mesh_ptr->vertices[index2]);
	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.dir.x, d = v0.x - ray.pos.x;
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.dir.y, h = v0.y - ray.pos.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.dir.z, l = v0.z - ray.pos.z;

	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;

	double inv_denom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;

	if (beta < 0.0)
		return (false);

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;

	if (gamma < 0.0)
		return (false);

	if (beta + gamma > 1.0)
		return (false);

	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;

	if (t < kEpsilon)
		return (false);
	in->localGeo.t = t;
	in->localGeo.pos = ray.pos + ray.dir*t;
	in->localGeo.normal = normal;
	return true;
}
bool FlatMeshTriangle::intersectP(Ray& ray){
	
}