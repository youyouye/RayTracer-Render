#ifndef CAMERA_H_
#define CAMERA_H_
#include"sampler.h"
#include"Ray.h"
#include "vector.h"
class Camera{
public:
	Camera();
	Camera(const Vector3 &eye,const Vector3 &target,const Vector3 &up,float fox,int width,int height){
		this->eye = eye;
		this->target = target;
		this->up = up;
		this->fox = fox;
		width_recp = 1. / (float)width;
		height_recp = 1. / (float)height;
		ratio = (float)width / height;
		direction = (target - eye).normalize();
		x_direction = Vector3(0, 0, 1).cross(direction * -1).normalize();
		y_direction = x_direction.cross(direction).normalize();
		x_spacing = (2.0*ratio) / (float)width;
		y_spacing = 2.0 / (float)height;
	}
	~Camera();
	void generateRay(Sample& sample,Ray* ray,bool jitter,unsigned short* X);
public:
	Vector3 eye;
	Vector3 target;
	Vector3 up;
	float fox;
private:
	float width_recp;
	float height_recp;
	float ratio;
	Vector3 direction;
	Vector3 x_direction;
	Vector3 y_direction;
	float x_spacing;
	float y_spacing;
};



#endif
