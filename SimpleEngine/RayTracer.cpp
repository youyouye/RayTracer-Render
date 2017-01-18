#include "RayTracer.h"
#include "vector.h"
#include "variables.h"
#include <algorithm>
void RayTracer::trace(Ray& ray, int depth, Color& color){
	if (depth > 5)
	{
		color = Color(0, 0, 0, 1);
		return;
	}
	LocalGeo local;
	Intersection in;
	BRDF brdf;
	if (!interset(ray, &thit, &in))
	{
		color = Color(0, 0, 0, 1);
		return;
	}
	color = Color(0, 0, 0, 1);
	in.primitive->getBRDF(in.localGeo,&brdf);
	Color finalcolor(0,0,0,0);
	Ray lray;
	Color lcolor;
	for (auto i = lights.begin(); i !=lights.end(); i++)
	{
		(*i)->generateLightRay(in.localGeo,&lray,&lcolor);
		if (!intersectP(lray))
		{
			thit++;
			finalcolor = finalcolor+(*shading(in.localGeo,brdf,lray,lcolor));
		}
	}
	color = color+brdf.ka+brdf.emission+finalcolor;
	color.r = std::min(color.r, 1.0f);	color.b = std::min(color.b, 1.0f);
	color.g = std::min(color.g, 1.0f);	color.a = std::min(color.a, 1.0f);

	if ((brdf.kr.r>0 )||( brdf.kr.g>0 )|| (brdf.kr.b>0))
	{
		Ray reflectRay;
		Color tempColor;
		createReflectRay(in.localGeo, reflectRay);
		trace(reflectRay,depth+1,tempColor);
		if (tempColor.r>0||tempColor.g>0||tempColor.b>0)
		{
			int  sss = 0;
			int eee = 0;
		}
		color = color + brdf.kr*(tempColor);
		color.r = std::min(color.r, 1.0f);	color.b = std::min(color.b, 1.0f);
		color.g = std::min(color.g, 1.0f);	color.a = std::min(color.a, 1.0f); 
	}
}
Color* RayTracer::shading(LocalGeo local, BRDF brdf, Ray lray, Color lcolor){
	float nDotL = Vector3(local.normal).normalize().dot(lray.dir);
	Color lambert = brdf.kd*lcolor*std::max(nDotL, 0.0f);
	Vector3 eyedirn =(Vector3(eye[0],eye[1],eye[2]) - Vector3(local.pos)).normalize();
	Vector3 half = (lray.dir + eyedirn).normalize();
	float nDotH = Vector3(local.normal).normalize().dot(half);
	Color phong = brdf.ks*lcolor*std::pow(std::max(nDotH,0.0f),brdf.shininess);
	return &Color(lambert+phong);
}
void RayTracer::createReflectRay(LocalGeo local, Ray& ray){
	Vector3 d = local.pos - Vector3(eye[0], eye[1], eye[2]);
	Vector3 r = d - Vector3(local.normal).normalize() * 2 * (d.dot(local.normal.normalize()));
	ray.dir = r.normalize();
	ray.pos = local.pos;
}
bool RayTracer::interset(Ray& ray, float* thit, Intersection* in){
	Intersection* temp;
	temp = &Intersection(); temp->localGeo = LocalGeo();
	temp->localGeo.t = 10000;
	for (auto i = primitives.begin(); i != primitives.end(); i++)
	{
		if ((*i)->interset(ray, thit, in))
		{
			if (in->localGeo.t >0.0001)
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
	else if (temp->localGeo.t < 0.0001 || temp->localGeo.t>ray.t_max){
		return false;
	}
	else{
		*in = *temp;
		return true;
	}
}
bool RayTracer::intersectP(Ray &ray){
	float t;
	Intersection i;
	return interset(ray,&t,&i);
}
