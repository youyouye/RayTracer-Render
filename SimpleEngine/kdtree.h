#ifndef KDNODE_H_
#define KDNODE_H_
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
	bool hit(Ray& ray, float& t,float& tmin,Intersection& intersection);
public:
	BBox bbox;
	KDNode *left;
	KDNode *right;
	bool leaf;
	std::vector<std::shared_ptr<Primitive>> triangles;	//only for triangles
};

#endif
