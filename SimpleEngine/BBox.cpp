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
	double ox = ray.pos.x; double oy = ray.pos.y; double oz = ray.pos.z;
	double dx = ray.dir.x; double dy = ray.dir.y; double dz = ray.dir.z;

	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;
	
	double a = 1.0 / dx;
	if (a>=0){
		tx_min = (x0 - ox)*a;
		tx_max = (x1 - ox)*a;
	}
	else{
		tx_min = (x1 - ox)*a;
		tx_max = (x0 - ox)*a;
	}
	double b = 1.0 / dy;
	if (b>=0)
	{
		ty_min = (y0 - oy)*b;
		ty_max = (y1 - oy)*b;
	}
	else{
		ty_min = (y1 - oy)*b;
		ty_max = (y0 - oy)*b;
	}
	double c = 1.0 / dz;
	if (c>=0)
	{
		tz_min = (z0 - oz)*c;
		tz_max = (z1 - oz)*c;
	}
	else{
		tz_min = (z1 - oz)*c;
		tz_max = (z0 - oz)*c;
	}
	double t0, t1;
	if (tx_min > ty_min)
		t0 = tx_min;
	else
		t0 = ty_min;
	if (tz_min > t0)
		t0 = tz_min;
	if (tx_max < ty_max)
		t1 = tx_max;
	else
		t1 = ty_max;
	if (tz_max<t1)
		t1 = tz_max;
	return (t0<t1 && t1>0.0001);
}

void BBox::expand(BBox bbox)
{
	if (bbox.x0 < x0) x0 = bbox.x0;
	if (bbox.y0 < y0) y0 = bbox.y0;
	if (bbox.z0 < z0) z0 = bbox.z0;
	
	if (bbox.x1 > x1) x1 = bbox.x1;
	if (bbox.y1 < y1) y1 = bbox.y1;
	if (bbox.z1 < z1) z1 = bbox.z1;
}

int BBox::longestAxis()
{
	Vector3 diff = Vector3(x1, y1, z1) - Vector3(x0,y0,z0);
	if (diff.x > diff.y && diff.x > diff.z) return 0;
	if (diff.y > diff.x && diff.y > diff.z) return 1;
	return 2;
}
