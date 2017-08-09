#include "SphericalMap.h"
#include "math.h"

SphericalMap::SphericalMap()
{
}


SphericalMap::~SphericalMap()
{
}

void SphericalMap::getPixelCoordinates(
	const Vector3& local_hit_point,
	const int hres,
	const int vres,
	int& row,
	int& column
	)const
{
	float theta = acos(local_hit_point.y);
	float phi = atan2(local_hit_point.x,local_hit_point.z);
	if (phi < 0.0)
		phi += TWO_PI;
	float u = phi*invTWO_PI;
	float v = 1 - theta*invPI;
	column = (int)((hres-1)*u);
	row = (int)((vres-1)*v);
}

