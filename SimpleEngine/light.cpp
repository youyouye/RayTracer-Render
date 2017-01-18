#include "light.h"

void PLight::generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor){
	(*lray).t_min = 0.00003;
	(*lray).t_max = (local.pos - point).length();
	(*lray).pos = local.pos;
	(*lray).dir = Vector3((local.pos - point)).normalize();
	(*lray).pos = (*lray).pos + (*lray).dir*0.001;
	(*lcolor) = lc;
}

void DLight::generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor){
	(*lray).t_min = 0.00003;
	(*lray).pos = local.pos;
	if (Vector3(local.normal).dot(direction) >= 0){
		(*lray).dir = direction.normalize();
	}else{
		(*lray).dir = Vector3(-direction.x,-direction.y,-direction.z).normalize();	}

	(*lray).pos = (*lray).pos + (*lray).dir*0.001;
	(*lcolor) = lc;
}

