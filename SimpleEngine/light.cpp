#include "light.h"

void PLight::generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor){
	(*lray).t_min = 0.00001;
	(*lray).t_max = std::fabs((local.pos - point).length());
	(*lray).pos = local.pos;
	(*lray).dir = Vector3((point - local.pos)).normalize();
	(*lray).pos = (*lray).pos + (*lray).dir*0.0003f;
	(*lcolor) = lc;
}

void DLight::generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor){
	(*lray).t_min = 0.00003;
	(*lray).pos = local.pos;
	if (Vector3(local.normal).dot(direction) >= 0){
		(*lray).dir = direction.normalize();
	}else{
		(*lray).dir = Vector3(-direction.x,-direction.y,-direction.z).normalize();	}

	(*lray).pos = (*lray).pos + (*lray).dir*0.0003f;
	(*lcolor) = lc;
}

