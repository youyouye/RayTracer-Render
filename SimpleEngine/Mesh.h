#ifndef MESH_H_
#define MESH_H_
#include <vector>
#include "vector.h"
using namespace std;
class Mesh
{
public:
	Mesh();
	~Mesh();
public:
	vector<Vector3> vertices;
	vector<int> indices;
	vector<Normal> normals;
	vector<vector<int>> vertexFaces;
	vector<float> u;
	vector<float> v;
	int num_vertices;
	int num_triangles;
};

#endif