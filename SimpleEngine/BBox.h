#ifndef _BBOX__H_
#define  _BBOX__H_
#include "Ray.h"
#include "Point.h"
class BBox
{
public:
	BBox();
	BBox(const float x0,const float x1,
		const float y0, const float y1,
		const float z0, const float z1);
	BBox(const Point p0,const Point p1);
	BBox(const BBox& bbox);
	~BBox();
	BBox& operator=(const BBox& rhs);
	bool hit(const Ray& ray) const;
	bool inside(const Point& p) const;
public:
	float x0, y0, z0, x1, y1, z1;
};

#endif