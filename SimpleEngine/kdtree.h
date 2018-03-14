#pragma once
#include <vector>
#include <memory>
#include "BBox.h"
#include "Primitive.h"
#include "Ray.h"

class KDNode 
{
public:
	KDNode() = default;
	KDNode* build(const std::vector<std::shared_ptr<Primitive>>& tris,int depth);
	bool hit(Ray& ray,float& t,Intersection& intersection);
	bool hit(Ray& ray, float& t, std::vector<Intersection>& intersections);
public:
	BBox bbox;
	KDNode *left;
	KDNode *right;
	bool leaf;
	std::vector<std::shared_ptr<Primitive>> triangles;	//only for triangles
};

