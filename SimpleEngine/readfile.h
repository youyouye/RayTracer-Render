#ifndef READFILE_H_
#define READFILE_H_
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include "vector.h"
#include "light.h"
#include "Primitive.h"

class ReadFile{
public:
	ReadFile() {
		ambient[0] = 0.2;
		ambient[1] = 0.2;
		ambient[2] = 0.2;
		mirror[0] = 0; mirror[1] = 0; mirror[2] = 0; mirror[3] = 0;
	}
	~ReadFile(){}
	void readfile(const char *name);
	bool readvals(std::stringstream &s, const int numvals, float * values);

public:
	int maxdepth;
	std::string output;
	float camera[10];

	//Materials
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float emission[4];
	float mirror[4];
	float shiness;
	//Lights
	std::vector<std::shared_ptr<Light>> lights;
	//shape;
	std::vector<std::shared_ptr<Primitive>> primitives;
	//vertex;
	int maxverts; //count
	std::vector<Vector3> vertex;
};
#endif