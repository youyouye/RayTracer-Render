#include "Primitive.h"
#include "Ray.h"
#include "material.h"
#include "BBox.h"

BBox Primitive::getBoundingBox(){
	return BBox();
}

Vector3 Primitive::getSpecialVec(){
	return Vector3(0, 0, 0); 
}

GeometricPrimitive::GeometricPrimitive()
{
}
GeometricPrimitive::~GeometricPrimitive(){
	delete shape;
	delete mat;
}

bool GeometricPrimitive::interset(Ray& ray, float* thit, Intersection* in){
	LocalGeo olocal;
	if (!shape->intersect(ray, thit, &olocal)) return false;
	in->primitive = this;
	in->localGeo = olocal;
	return true;
}
bool GeometricPrimitive::intersectP(Ray& ray){
	float th = 0;
	LocalGeo olocal;
	return shape->intersect(ray,&th,&olocal);
}
BRDF* GeometricPrimitive::getBRDF(LocalGeo& local){
	return mat->constantBRDF;
}

Vector3 GeometricPrimitive::getSpecialVec(){
	return shape->getSpecVec();
}

AggregatePrimitive::AggregatePrimitive(){
}
AggregatePrimitive::~AggregatePrimitive(){
}

bool AggregatePrimitive::interset(Ray& ray, float* thit, Intersection* in){
	Intersection* temp;
	temp = &Intersection(); temp->localGeo = LocalGeo();
	temp->localGeo.t = 10000;
	for (auto i = objects.begin(); i != objects.end(); i++)
	{
		if ((*i)->interset(ray, thit, in))
		{
			if (in->localGeo.t >ray.t_min && in->localGeo.t <ray.t_max)
			{
				if (in->localGeo.t<temp->localGeo.t){
					*temp = *in;
				}
			}
		}
	}
	if (temp->localGeo.t == 10000){
		return false;
	}
	else{
		*in = *temp;
		return true;
	}
}
bool AggregatePrimitive::intersectP(Ray& ray){
	return false;
}
BRDF* AggregatePrimitive::getBRDF(LocalGeo& local){
	return nullptr;
}
void AggregatePrimitive::setMaterial(const Material& marptr){
	for (auto i = objects.begin(); i != objects.end();i++)
	{
	}
}
void AggregatePrimitive::addObject(const std::shared_ptr<Primitive> objectptr){
	objects.push_back(objectptr);
}






