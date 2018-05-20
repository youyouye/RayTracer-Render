#include "Point.h"
#include "mymath.h"
#include "vector.h"
Point::Point(Vector3 &v){
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}
float Point::length() const{
	return sqrtf(x*x+y*y+z*z);
}
Point Point::operator + (const Vector3 &p) const{
	return Point(x + p.x,y+p.y,z+p.z);
}
