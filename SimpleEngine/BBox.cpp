#include "BBox.h"

BBox::BBox()
{
}

BBox::BBox(Vector3 bottom, Vector3 tail)
{
	x0 = bottom.x;
	y0 = bottom.y;
	z0 = bottom.z;
	x1 = tail.x;
	y1 = tail.y;
	z1 = tail.z;
}

BBox::~BBox()
{
}

bool BBox::hit(const Ray& ray) const{
	double tx1 = (x0 - ray.pos.x)*ray.dir.x;
	double tx2 = (x1 - ray.pos.x)*ray.dir.x;
	double tmin = std::fmin(tx1,tx2);
	double tmax = std::fmax(tx1,tx2);

	double ty1 = (y0 - ray.pos.y)*ray.dir.y;
	double ty2 = (y1 - ray.pos.y)*ray.dir.y;

	tmin = std::fmax(tmin,std::fmin(ty1,ty2));
	tmax = std::fmin(tmax, std::fmax(ty1, ty2));

	double tz1 = (z0 - ray.pos.z)*ray.dir.z;
	double tz2 = (z1 - ray.pos.z)*ray.dir.z;

	tmin = std::fmax(tmin, std::fmin(tz1, tz2));
	tmax = std::fmin(tmax, std::fmax(tz1, tz2));
	
	return tmax >= tmin;
}

void BBox::expand(BBox bbox)
{
	if (bbox.x0 < x0) x0 = bbox.x0;
	if (bbox.y0 < y0) y0 = bbox.y0;
	if (bbox.z0 < z0) z0 = bbox.z0;
	
	if (bbox.x1 > x1) x1 = bbox.x1;
	if (bbox.y1 > y1) y1 = bbox.y1;
	if (bbox.z1 > z1) z1 = bbox.z1;
}

int BBox::longestAxis()
{
	Vector3 diff = Vector3(x1, y1, z1) - Vector3(x0,y0,z0);
	if (diff.x > diff.y && diff.x > diff.z) return 0;
	if (diff.y > diff.x && diff.y > diff.z) return 1;
	return 2;
}
