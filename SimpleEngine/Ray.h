#ifndef RAY_H_
#define RAY_H_

#include "Point.h"
#include "vector.h"
class Primitive;
class Ray
{
public:
	Ray() :t_min(0.00001), t_max(100000){
	}
	Ray(Point p) : t_min(0.00001),t_max(100000){
		pos = p;
	}
	~Ray(){}

public:
	Point pos;
	Vector3 dir;
	float t_min, t_max;
};

class Intersection
{
public:
	Intersection(){}
	~Intersection(){}

public:
	LocalGeo localGeo;
	Primitive* primitive;
};



#endif