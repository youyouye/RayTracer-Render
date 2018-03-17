#include "kdtree.h"

KDNode* KDNode::build(const std::vector<std::shared_ptr<Primitive>>& tris, int depth)
{
	KDNode* node = new KDNode();
	node->leaf = false;
	node->triangles = std::vector<std::shared_ptr<Primitive>>();
	node->left = nullptr;
	node->right = nullptr;
	node->bbox = BBox();

	if (tris.size() == 0)
		return node;
	if (depth > 25 || tris.size() <= 6)
	{
		node->triangles = tris;
		node->leaf = true;
		node->bbox = tris[0]->getBoundingBox();
		for (long i = 1;i < tris.size();i++)
		{
			node->bbox.expand(tris[i]->getBoundingBox());
		}
		node->left = new KDNode();
		node->right = new KDNode();
		node->left->triangles = std::vector<std::shared_ptr<Primitive>>();
		node->right->triangles = std::vector<std::shared_ptr<Primitive>>();
		return node;
	}

	node->bbox = tris[0]->getBoundingBox();
	Vector3 midpt;
	for (long i = 1;i < tris.size();i++)
	{
		node->bbox.expand(tris[i]->getBoundingBox());
		midpt = midpt + tris[i]->getMidPoint() * (double)(1.0 / tris.size());
	}

	std::vector<std::shared_ptr<Primitive>> left_tris;
	std::vector<std::shared_ptr<Primitive>> right_tris;
	
	int axis = node->bbox.longestAxis();
	for (int i = 0;i < tris.size();i++)
	{
		switch (axis)
		{
		case 0:
			midpt.x >= tris[i]->getMidPoint().x ? right_tris.push_back(tris[i]) : left_tris.push_back(tris[i]);
			break;
		case 1:
			midpt.y >= tris[i]->getMidPoint().y ? right_tris.push_back(tris[i]) : left_tris.push_back(tris[i]);
			break;
		case 2:
			midpt.z >= tris[i]->getMidPoint().z ? right_tris.push_back(tris[i]) : left_tris.push_back(tris[i]);
			break;
		}
	}
	
	if (tris.size() == left_tris.size() || tris.size() == right_tris.size())
	{
		node->triangles = tris;
		node->leaf = true;
		node->bbox = tris[0]->getBoundingBox();
		for (long i = 0; i < tris.size(); i++)
		{
			node->bbox.expand(tris[i]->getBoundingBox());
		}
		node->left = new KDNode();
		node->right = new KDNode();
		node->left->triangles = std::vector<std::shared_ptr<Primitive>>();
		node->right->triangles = std::vector<std::shared_ptr<Primitive>>();
		return node;
	}
	node->left = build(left_tris, depth + 1);
	node->right = build(right_tris, depth + 1);
	return node;
}

bool KDNode::hit(Ray& ray, float& t, float& tmin, Intersection& in)
{
	double distance;
	if (bbox.hit(ray, distance))
	{
		if (left->triangles.size() > 0 || right->triangles.size() > 0)
		{
			bool hitleft = left->hit(ray, t,tmin, in);
			bool hitright = right->hit(ray,t, tmin,in);
			return hitright || hitright;
		}
		else 
		{
			for (int i = 0;i < triangles.size();i++)
			{
				if (triangles[i]->interset(ray,&t,tmin,&in))
					return true;
			}
		}
		return false;
	}
	return false;
}

bool KDNode::hit(Ray& ray, float& t, float& tmin, std::vector<Intersection>& intersections)
{
	double distance;
	if (bbox.hit(ray,distance))
	{
//		if (distance > tmin) return false;
		bool hit_flag = false;
		bool hitleft = false;
		bool hitright = false;
		if (!this->leaf)
		{
			hitleft = left->hit(ray, t,tmin, intersections);
			hitright = right->hit(ray, t,tmin, intersections);
			return hitleft || hitright;
		}
		else 
		{
			long tir_size = this->triangles.size();
			for (long i = 0;i < triangles.size();i++)
			{
				Intersection temp;
				if (this->triangles[i]->interset(ray,&t,tmin, &temp))
				{
					tmin = temp.localGeo.t < tmin ? temp.localGeo.t : tmin;
					hit_flag = true;
					intersections.push_back(temp);
				}
			}
			if (hit_flag)
				return true;
		}
	}
	return false;
}
