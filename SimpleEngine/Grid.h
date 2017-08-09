#ifndef GRID_H_
#define GRID_H_
#include "BBox.h"
#include "Primitive.h"
#include "Mesh.h"
#include <vector>
#include <memory>
class Grid :public AggregatePrimitive
{
public:
	Grid();
	Grid(Mesh* meshPtr);
	~Grid();

	BBox getBoundingBox();
	void setupCells();
	bool intersectP(Ray& ray, float* thit, Intersection* in);
	bool shadowIntersect(Ray& ray);

	void read_falt_triangles(char* filename);
	void read_smooth_triangles(char* filename);

private:
	std::vector<std::shared_ptr<Primitive>> cells;
	BBox bbox;
	Mesh* meshPtr;
	int nx, ny, nz; //number of cells in three directions
	Vector3 minCoordinates();
	Vector3 maxCoordinates();

	void read_ply_file(char* filename,const int triangleType);
};

#endif