#ifndef MESHTRIANGLE_H_
#define MESHTRIANGLE_H_
#include "Mesh.h"
#include "Primitive.h"
class MeshTriangle : public Primitive
{
public:
	MeshTriangle();
	MeshTriangle(Mesh* _mesh_ptr,const int i1,const int i2,const int i3);
	virtual ~MeshTriangle();
	virtual MeshTriangle*
		clone(void) const = 0;
	MeshTriangle(const MeshTriangle& mt);
	MeshTriangle& operator=(const MeshTriangle& rhs);
	bool interset(Ray& ray, float* thit, Intersection* in);
	bool intersectP(Ray& ray) ;
	virtual Normal getNormal() const;
	void computeNormal(const bool reverseNormal);
	BBox getBoundingBox();
protected:
	float interpolate_u(const float beta,const float gamma) const;
	float interpolate_v(const float beta, const float gamma) const;
public:
	Mesh* mesh_ptr;
	Normal normal;
	float area;
	int index0, index1, index2;
};

#endif