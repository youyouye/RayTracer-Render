#ifndef _BBOX__H_
#define  _BBOX__H_
#include "Ray.h"
class BBox
{
public:
	BBox();
	~BBox();
	bool hit(const Ray& ray) const;
public:
	float x0, y0, z0, x1, y1, z1;
};

#endif