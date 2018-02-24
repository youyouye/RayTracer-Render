#include "kdtree.h"

KDNode* KDNode::build(const std::vector<Triangle*>& tris, int depth) 
{
	KDNode* node = new KDNode();
	node->triangles = tris;
	node->left = nullptr;
	node->right = nullptr;
	node->bbox = BBox();

	if (tris.size() == 0)
		return node;
	if (tris.size() == 1)
	{
		node->bbox = tris[0]->getBoundingBox();
		node->left = new KDNode();
		node->right = new KDNode();
		node->left->triangles = std::vector<Triangle*>();
		node->right->triangles = std::vector<Triangle*>();
		return node;
	}
	node->bbox = tris[0]->getBoundingBox();
	for (int i = 1;i < tris.size();i++)
	{
		node->bbox.expand(tris[i]->getBoundingBox());
	}

	Vector3 midpt;
	for (int i = 0;i < tris.size();i++)
	{
		midpt = midpt + tris[i]->getMidPoint() * (1.0 / tris.size());
	}

	std::vector<Triangle*> left_tris;
	std::vector<Triangle*> right_tris;
	
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
		case 2:
			midpt.z >= tris[i]->getMidPoint().z ? right_tris.push_back(tris[i]) : left_tris.push_back(tris[i]);
		}
	}
	if (left_tris.size() == 0 && right_tris.size() > 0)
		left_tris = right_tris;
	if (right_tris.size() == 0 && left_tris.size() > 0)
		right_tris = left_tris;

	int matches = 0;
	for (int i = 0;i < left_tris.size();i++)
	{
		for (int j = 0;j < right_tris.size();j++)
		{
			if (left_tris[i] == right_tris[j])
			{
				matches++;
			}
		}
	}

	if ((float)matches/left_tris.size() < 0.5 && (float)matches/right_tris.size() < 0.5 )
	{
		node->left = build(left_tris, depth + 1);
		node->right = build(right_tris, depth + 1);
	}
	else 
	{
		node->left = new KDNode();
		node->right = new KDNode();
		node->left->triangles = std::vector<Triangle*>();
		node->left->triangles = std::vector<Triangle*>();
	}
	return node;
}

bool KDNode::hit(const Ray& ray, float& t, float& tmin, Intersection& intersection)
{
	if (bbox.hit(ray))
	{
		Normal normal;
		bool hit_tri = false;
		Vector3 hit_pt, local_hit_pt;

		if (left->triangles.size() > 0 || right->triangles.size() > 0)
		{
			bool hitleft = left->hit(ray, t, tmin, intersection);
			bool hitright = right->hit(ray,t,tmin,intersection);
			return hitright || hitright;
		}
		else 
		{
			for (int i = 0;i < triangles.size();i++)
			{
				if (triangles[i]->intersect())
				{
				}
			}
		}

	}

}





















