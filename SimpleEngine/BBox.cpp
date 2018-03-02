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
	if (std::abs(dx) < 0.000001f)
	{
		if (ox < x1 || ox > x0)
			return false;
	}
	else 
	{
		if (dx >= 0)
		{
			tx_min = (x0 - ox) / dx;
			tx_max = (x1 - ox) / dx;
		}
		else
		{
			tx_min = (x1 - ox) / dx;
			tx_max = (x0 - ox) / dx;
		}
	}
	if (std::abs(dy) < 0.000001f)
	{
		if (oy < y1 || oy > y0)
			return false;
	}
	else 
	{
		if (dy >= 0)
		{
			ty_min = (y0 - oy) / dy;
			ty_max = (y1 - oy) / dy;
		}
		else
		{
			ty_min = (y1 - oy) / dy;
			ty_max = (y0 - oy) / dy;
		}
	}
	if (abs(dz) < 0.000001f)
	{
		if (oz < z1 || oz > z0)
			return false;
	}
	else 
	{
		if (dz >= 0)
		{
			tz_min = (z0 - oz) / dz;
			tz_max = (z1 - oz) / dz;
		}
		else
		{
			tz_min = (z1 - oz) / dz;
			tz_max = (z0 - oz) / dz;
		}
	}
	double t0, t1;
	t0 = std::fmax(tz_min, std::fmax(tx_min, ty_min));
	t1 = std::fmin(tz_max, std::fmin(tx_max, ty_max));
	
	return t0 < t1;
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
