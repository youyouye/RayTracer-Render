#ifndef VECTOR_H_
#define VECTOR_H_
#include"math.h"
#include "Point.h"
class Normal;
class Vector2{
public:
	Vector2(float x=0.0f, float y=0.0f){ 
		this->x = x; 
		this->y = y;
	};
public:
	float x;
	float y;
};

class Vector3{
public:
	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3(Point p){
		this->x = p.x;
		this->y = p.y;
		this->z = p.z;
	}
	Vector3(Normal n);
	float length() const;
	Vector3 normalize() const;
	float dot(const Vector3 &v) const;
	Vector3 cross(const Vector3 &v) const;
	Vector3 interpolate(const Vector3 &v, float factor) const;

	Vector3 operator+(const Vector3 &v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	};

	Vector3 operator-(const Vector3 &v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	};

	Vector3 operator*(float factor) const {
		return Vector3(x * factor, y * factor, z * factor);
	};

	bool operator==(const Vector3 &v) const {
		return floatEqual(x, v.x) && floatEqual(y, v.y) && floatEqual(z, v.z);
	};
public:
	float x;
	float y;
	float z;
};

class Normal
{
public:
	Normal(float x=0.0f,float y=0.0f,float z=0.0f){
		this->x = x;
		this->y = y;
		this->z = z;
	};
	Normal(Point p){
		this->x = p.x;
		this->y = p.y;
		this->z = p.z;
	};
	Normal(Vector3 v){
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	};
	~Normal(){}
	float length() const;
	Normal operator+(const Normal &n)const{
		return Normal(x+n.x,y+n.y,z+n.z);
	};
	Normal operator-(const Normal &n)const{
		return Normal(x-n.x,y-n.y,z-n.z);
	};
	Normal normalize() const;

public:
	float x, y, z;
};

class LocalGeo
{
public:
	LocalGeo(){

	}
	~LocalGeo(){}

public:
	Point pos;
	Normal normal;
	float t;
};


#endif