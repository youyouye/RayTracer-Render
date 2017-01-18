#ifndef CAMERA_H_
#define CAMERA_H_
#include"sampler.h"
#include"Ray.h"
#include "vector.h"
class Camera{
public:
	Camera();
	Camera(Vector3 &eye, Vector3 &target, Vector3 &up,float fox){
		this->eye = eye;
		this->target = target;
		this->up = up;
		this->fox = fox;
	}
	~Camera();
	void generateRay(Sample& sample,Ray* ray);
public:
	Vector3 eye;
	Vector3 target;
	Vector3 up;
	float fox;
};



#endif