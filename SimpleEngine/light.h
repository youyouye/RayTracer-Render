#ifndef LIGHT_H_
#define LIGHT_H_
#include "vector.h"
#include "Ray.h"
#include "color.h"
class Light{
public:
	virtual void generateLightRay(LocalGeo& local,Ray* lray,Color* lcolor)=0;
	virtual Vector3 getIntensity()=0;
};

class PLight : public Light{
public:
	PLight();
	PLight(Point p){
		this->point = p;
	};
	PLight(Vector3 d, Color color){
		this->point = d;
		this->lc = color;
	};
	void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor);
	Vector3 getIntensity(){
		return intensity;
	}
public:
	Vector3 intensity;
	Vector3 point;
	Color lc;
};

class DLight : public Light{
public:
	DLight();
	DLight(Vector3 d):lc(0,0,0,0),intensity(0,0,0){
		this->direction = d;
	};
	DLight(Vector3 d,Color color):intensity(0,0,0){
		this->direction = d;
		this->lc = color;
	};
	DLight(Vector3 d,Vector3 inten) :lc(0,0,0,0){
		this->direction = d;
		this->intensity = inten;
	}
	void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor);
	Vector3 getIntensity(){
		return intensity;
	}
public:
	Vector3 direction;
	Vector3 intensity;
	Color lc;
};

#endif