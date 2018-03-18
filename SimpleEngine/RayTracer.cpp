#include "RayTracer.h"
#include "vector.h"
#include "variables.h"
#include "kdtree.h"
#include "rand48/erand48.h"
#include "Ray.h"
#include "material.h"
#include <algorithm>

RayTracer::~RayTracer()
{
	delete kdtree;
}

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
		color = color + brdf.kr*(tempColor);
		color.r = std::min(color.r, 1.0f);	color.b = std::min(color.b, 1.0f);
		color.g = std::min(color.g, 1.0f);	color.a = std::min(color.a, 1.0f); 
	}
}

void RayTracer::kd_trace(Ray& ray, int depth, Color& color, unsigned short*X)
{
	if (depth > 5)
	{
		color = Color(0, 0, 0, 1);
		return;
	}
	LocalGeo local;
	Intersection in;
	BRDF brdf;
	if (!kdTreeInterset(ray, &thit, in))
	{
		color = Color(0, 0, 0, 1);
		return;
	}
	auto material = in.primitive->getMaterial();
	if (material->material_type_ == MaterialType::EMIT)
	{
		color = material->default_color_;
		return;
	}
	color = Color(0, 0, 0, 1);
	in.primitive->getBRDF(in.localGeo, &brdf);
	Color finalcolor(0, 0, 0, 0);
	Ray lray;
	Color lcolor;
	for (auto i = lights.begin(); i != lights.end(); i++)
	{
		(*i)->generateLightRay(in.localGeo, &lray, &lcolor);
		if (!kdTreeIntersetP(lray))
		{
			thit++;
			finalcolor = finalcolor + (*shading(in.localGeo, brdf, lray, lcolor));
		}
	}
	color = color + in.primitive->getColor(in.localGeo.pos) + finalcolor;
	color.r = std::min(color.r, 1.0f);	color.b = std::min(color.b, 1.0f);
	color.g = std::min(color.g, 1.0f);	color.a = std::min(color.a, 1.0f);
	double p = color.r > color.g && color.r > color.b ? color.r : color.g > color.b ? color.g : color.b;

	double random = erand48(X);
	if (random < p *0.9)
	{
		color = color*(0.9 / p);
	}
	//mirror reflection
	if ((brdf.kr.r > 0) || (brdf.kr.g > 0) || (brdf.kr.b > 0))
	{
		Ray reflectRay;
		Color tempColor;
		createReflectRay(in.localGeo, reflectRay);
		kd_trace(reflectRay, depth + 1, tempColor, X);
		color = color + brdf.kr*(tempColor);
		color.r = std::min(color.r, 1.0f);	color.b = std::min(color.b, 1.0f);
		color.g = std::min(color.g, 1.0f);	color.a = std::min(color.a, 1.0f);
	}
	else
	{
		Ray reflected = in.getReflectedRay(ray, X);
		Color temp_color;
		kd_trace(reflected, depth + 1, temp_color, X);
		color = color*temp_color;
		color.r = std::min(color.r, 1.0f);	color.b = std::min(color.b, 1.0f);
		color.g = std::min(color.g, 1.0f);	color.a = std::min(color.a, 1.0f);
	}
}

Color* RayTracer::shading(LocalGeo local, BRDF brdf, Ray lray, Color lcolor){
	Vector3 eyedirn = (Vector3(eye[0], eye[1], eye[2]) - Vector3(local.pos)).normalize();
	float nDotL = Vector3(local.normal).normalize().dot(lray.dir);
	Color lambert = brdf.kd*lcolor*std::max(nDotL, 0.0f);
	Vector3 half = (lray.dir + eyedirn).normalize();
	float nDotH = Vector3(local.normal).normalize().dot(half);
	Color phong = brdf.ks*lcolor*std::pow(std::max(nDotH,0.0f),brdf.shininess);
	return new Color(lambert+phong); //TODO:memory leak...
}

void RayTracer::createReflectRay(LocalGeo local, Ray& ray){
	Vector3 d = local.pos - Vector3(eye[0], eye[1], eye[2]);
	Vector3 r = d - Vector3(local.normal).normalize() * 2 * (d.dot(local.normal.normalize()));
	ray.dir = r.normalize();
	ray.pos = local.pos+ray.dir*0.0003;
}

bool RayTracer::interset(Ray& ray, float* thit, Intersection* in){
	Intersection* temp;
	temp = &Intersection(); temp->localGeo = LocalGeo();
	temp->localGeo.t = 10000;
	for (auto i = primitives.begin(); i != primitives.end(); i++)
	{
		float tmin = INFINITY;
		if ((*i)->interset(ray, thit, tmin, in))
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
	}else{
		*in = *temp;
		return true;
	}
}

bool RayTracer::intersectP(Ray &ray){
	float t;
	Intersection i;
	return interset(ray,&t,&i);
}

void RayTracer::generateKDTree()
{
	kdtree = new KDNode();
	kdtree = kdtree->build(primitives, 0);
}

//TODO:如果多种方式都这么通用的话,就把这里改掉;
bool RayTracer::kdTreeInterset(Ray& ray, float* thit, Intersection& in)
{
	Intersection* temp;
	temp = &Intersection(); temp->localGeo = LocalGeo();
	temp->localGeo.t = 10000;

	std::vector<Intersection> all_in;
	float tmin = INFINITY;
	if (kdtree->hit(ray, *thit,tmin, all_in))
	{
		for (auto it = all_in.begin();it != all_in.end();it++)
		{
			if (it->localGeo.t > ray.t_min && it->localGeo.t < ray.t_max)
			{
				if (it->localGeo.t < temp->localGeo.t)
				{
					*temp = *it;
				}
			}
		}
	}

	if (temp->localGeo.t == 10000) {
		return false;
	}
	else {
		in = *temp;
		return true;
	}
}

bool RayTracer::kdTreeIntersetP(Ray& ray)
{
	float t;
	Intersection i;
	return kdTreeInterset(ray, &t, i);
}