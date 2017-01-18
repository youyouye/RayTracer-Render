#include "vector.h"


Vector3::Vector3(Normal n){
	this->x = n.x;
	this->y = n.y;
	this->z = n.z;
}


float
Vector3::length() const {
	return sqrtf(x * x + y * y + z * z);
}

Vector3
Vector3::normalize() const {
	float factor = 0;
	float length = this->length();
	if (length > 0) {
		factor = 1 / length;
	}
	return Vector3(x * factor, y * factor, z * factor);
};

float
Vector3::dot(const Vector3 &v) const {
	return x * v.x + y * v.y + z * v.z;
};

Vector3
Vector3::cross(const Vector3 &v) const {
	float X = y * v.z - z * v.y;
	float Y = z * v.x - x * v.z;
	float Z = x * v.y - y * v.x;
	return Vector3(X, Y, Z);
};

Vector3
Vector3::interpolate(const Vector3 &v, float factor) const {
	return *this + (v - *this) * factor;
};

Normal Normal::normalize() const {
	float factor = 0;
	float length = this->length();
	if (length > 0) {
		factor = 1 / length;
	}
	return Normal(x * factor, y * factor, z * factor);
}
float
Normal::length() const {
	return sqrtf(x * x + y * y + z * z);
}
