#ifndef POINT_H_
#define POINT_H_
class Vector3;
class Point
{
public:
	Point(float x=0.0f,float y=0.0f,float z=0.0f){
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Point(const Vector3 &v);
	~Point(){}
	float length() const;

	Point operator-(const Point &p) const{
		return Point(x-p.x,y-p.y,z-p.z);
	}
	Point operator+(const Vector3 &p) const;
	Point operator*(float factor) const {
		return Point(x * factor, y * factor, z * factor);
	}
public:
	float x, y, z;
};



#endif
