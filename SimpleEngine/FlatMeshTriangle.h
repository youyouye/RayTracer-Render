#ifndef FLATMESHTRIANGLE_H_
#define FLATMESHTRIANGLE_H_
#include "MeshTriangle.h"
class FlatMeshTriangle : public MeshTriangle
{
public:
	FlatMeshTriangle();
	FlatMeshTriangle(Mesh* mesh_ptr, const int i0, const int i1, const int i2);
	virtual FlatMeshTriangle* clone() const;
	FlatMeshTriangle(const FlatMeshTriangle& fmt);
	FlatMeshTriangle& operator=(const FlatMeshTriangle& rhs);
	~FlatMeshTriangle();
	bool interset(Ray& ray, float* thit, Intersection* in);
	bool intersectP(Ray& ray);
};

#endif