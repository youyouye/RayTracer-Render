#include "Ray.h"
#include "Primitive.h"
#include "material.h"
#include "rand48/erand48.h"

Ray Intersection::getReflectedRay(Ray ray, unsigned short * X)
{
	MaterialType type = this->primitive->getMaterial()->material_type_;
	if (type == MaterialType::SEPCULAR)
	{
		double roughess = 0.8;
		Vector3 reflected = ray.dir - Vector3(this->localGeo.normal) * 2 * Vector3(this->localGeo.normal).dot(ray.dir);
		reflected = Vector3(
			reflected.x + (erand48(X) - 0.5)*roughess,
			reflected.y + (erand48(X) - 0.5)*roughess,
			reflected.z + (erand48(X) - 0.5)*roughess
		).normalize();
		Ray ray;
		ray.pos = this->localGeo.pos+reflected*0.003;
		ray.dir = reflected;
		return ray;
	}
	if (type == MaterialType::DIFFUSE)
	{
		Vector3 nl = Vector3(this->localGeo.normal).dot(ray.dir) < 0 ? Vector3(this->localGeo.normal) : Vector3(this->localGeo.normal)*-1;
		double r1 = 2 * PI*erand48(X), r2 = erand48(X), r2s = sqrt(r2);
		Vector3 w = nl, u = ((fabs(w.x)>.1?Vector3(0,1,0):Vector3(1,0,0)) % w).normalize(), v = w%u;
		Vector3 d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1 - r2)).normalize();
		Ray ray;
		ray.pos = this->localGeo.pos;
		ray.dir = d;
		return ray;
	}
}
