#include "camera.h"
#include "variables.h"
#include "matrix.h"
Camera::Camera(){

}
Camera::~Camera(){
}
void Camera::generateRay(Sample& sample, Ray* ray){
	
	Vector3 axisZ = (eye - target).normalize();
	Vector3 axisX = up.cross(axisZ).normalize();
	Vector3 axisY = axisZ.cross(axisX);
	float a = tanf(fox/2*PI/180)*((float)width/(float)height)*((sample.x+0.5-((float)width/2))/((float)width/2));
	float b = tanf(fox / 2*PI/180)*((((float)height/2)-sample.y-0.5)/((float)height/2));
	Vector3 dir = (axisX*a + axisY*b - axisZ).normalize();
	ray->pos = Point(eye.x,eye.y,eye.z);
	ray->dir = dir;
	/*
	float a = -1 + 2 * (sample.x + 0.5) / width;
	float b = -1 + 2 * (sample.y + 0.5) / height;
	Vector3 w = Vector3(a, b, 1);
	ray->pos = Point(eye.x, eye.y, eye.z);
	ray->dir = w-eye;
	*/
}



