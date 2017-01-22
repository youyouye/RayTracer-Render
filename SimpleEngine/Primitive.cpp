#include "Primitive.h"
#include "Ray.h"
#include "material.h"

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
void GeometricPrimitive::getBRDF(LocalGeo& local, BRDF* brdf){
	*brdf = mat->constantBRDF;
}

AggregatePrimitive::AggregatePrimitive(){
}
AggregatePrimitive::~AggregatePrimitive(){
}

bool AggregatePrimitive::interset(Ray& ray, float* thit, Intersection* in){
	float t;
	Normal normal;
	Point hitPoint;
	bool hit = false;
	int numOfShapes = objects.size();
	for (int j = 0; j< numOfShapes; j++)
	{
		
	}
	return false;
}
bool AggregatePrimitive::intersectP(Ray& ray){
	return false;
}
void AggregatePrimitive::getBRDF(LocalGeo& local, BRDF* brdf){
	
}
void AggregatePrimitive::setMaterial(const Material& marptr){
	
}
void AggregatePrimitive::addObject(const std::shared_ptr<Shape> shapeptr){

}






