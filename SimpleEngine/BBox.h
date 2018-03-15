#ifndef _BBOX__H_
#define  _BBOX__H_
#include "Ray.h"
#include "vector.h"

class BBox
{
public:
	BBox();
	BBox(Vector3 bottom,Vector3 tail);
	~BBox();
	bool hit(const Ray& ray,double &t) const;
	void expand(BBox bbox);
	int longestAxis();
public:
	float x0, y0, z0, x1, y1, z1;
};

#endif