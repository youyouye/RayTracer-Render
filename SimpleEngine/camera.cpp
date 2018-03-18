#include "camera.h"
#include "variables.h"
#include "matrix.h"
#include "rand48/erand48.h"

Camera::Camera()
{

}

Camera::~Camera()
{
}

void Camera::generateRay(Sample& sample, Ray* ray,bool jitter,unsigned short* X)
{
	double x_jitter;
	double y_jitter;
	if (jitter)
	{
		x_jitter = (erand48(X)*x_spacing) - x_spacing*0.5;
		y_jitter = (erand48(X)*y_spacing) - y_spacing*0.5;
	}
	else 
	{
		x_jitter = 0;
		y_jitter = 0;
	}
	/*
	Vector3 axisZ = (eye - target).normalize();
	Vector3 axisX = up.cross(axisZ).normalize();
	Vector3 axisY = axisZ.cross(axisX);
	float a = tanf(fox/2*PI/180)*((float)width/(float)height)*((sample.x+0.5-((float)width/2))/((float)width/2));
	float b = tanf(fox / 2*PI/180)*((((float)height/2)-sample.y-0.5)/((float)height/2));
	Vector3 dir = (axisX*a + axisY*b - axisZ).normalize();
	ray->pos = Point(eye.x,eye.y,eye.z);
	ray->dir = dir;
	*/
	Vector3 pixel = eye + direction * 2;
	pixel = pixel - x_direction*ratio + x_direction*((sample.x*2*ratio)*width_recp) + x_jitter;
	pixel = pixel + y_direction - y_direction*((sample.y*2.0)*height_recp+y_jitter) + y_jitter;
	ray->pos = eye;
	ray->dir = (pixel - eye).normalize();
}



