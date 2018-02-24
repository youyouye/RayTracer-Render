#pragma once
#include <vector>
#include "BBox.h"
#include "Shape.h"
#include "Ray.h"

class KDNode 
{
public:
	KDNode() = default;
	KDNode* build(const std::vector<Triangle*>& tris,int depth);
	bool hit(const Ray& ray,float& t,float& tmin,Intersection& intersection);
public:
	BBox bbox;
	KDNode *left;
	KDNode *right;
	std::vector<Triangle*> triangles;
};

