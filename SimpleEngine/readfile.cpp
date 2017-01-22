#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>
#include "material.h"
#include "readfile.h"
#include "variables.h"
using namespace std;

void rightmultiply(const Matrix & M, stack<Matrix> &transfstack)
{
	Matrix &T = transfstack.top();
	T = T * M;
}

bool ReadFile::readvals(stringstream &s, const int numvals, float * values){
	for (int i = 0; i < numvals; i++){
		s >> values[i];
		if (s.fail())
		{
			cout << "Failed reading value" << endl;
			return false;
		}
	}
	return true;
}

void ReadFile::readfile(const char *name){
	width = 500;
	height = 500;

	ifstream in;
	string str,cmd;
	in.open(name);
	if (in.is_open()){
		stack<Matrix> transfstack;
		transfstack.push(Matrix().identify());
		getline(in,str);
		while (in)
		{
			if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#'))
			{
				stringstream s(str);
				s >> cmd;
				int i;
				float values[10];
				bool validinput;
				if (cmd == "size")
				{
					validinput = readvals(s,2,values);
					if (validinput)
					{
						width = values[0];
						height = values[1];
					}
				}
				else if (cmd == "maxdepth"){
					validinput = readvals(s,1,values);
					if (validinput)
					{
						maxdepth = values[0];
					}
				}
				else if (cmd == "output"){
				//	s >> filename;
				}
				else if (cmd == "camera"){
					validinput = readvals(s, 10, values);
					if (validinput)
					{
						eye[0] = values[0]; eye[1] = values[1]; eye[2] = values[2];
						for (int i = 0; i < 10; i++)
						{
							camera[i] = values[i];
						}
					}
				}
				else if (cmd == "maxverts"){
					validinput = readvals(s, 1, values);
					if (validinput)
					{
						maxverts = values[0];
					}
				}
				else if (cmd == "vertex"){
					validinput = readvals(s, 3, values);
					if (validinput)
					{
						vertex.push_back(Vector3(values[0],values[1],values[2]));
					}
				}
				else if (cmd == "sphere"){
					validinput = readvals(s, 4, values);
					if (validinput)
					{
						Sphere* sphere = new Sphere(values[3],Point(values[0],values[1],values[2]));
						Material* mat = new Material(&BRDF(Color(diffuse[0],diffuse[1],diffuse[2],1),
							Color(specular[0],specular[1],specular[2],1),Color(ambient[0],ambient[1],ambient[2],1),Color(mirror[0],mirror[1],mirror[2],1),Color(emission[0],emission[1],emission[2],1),shiness));
						primitives.push_back(make_shared<GeometricPrimitive>(sphere, mat, transfstack.top()));
					}
				}
				else if (cmd == "tri"){
					validinput = readvals(s, 3, values);
					if (validinput)
					{
						Triangle* tri = new Triangle(vertex[values[0]], vertex[values[1]], vertex[values[2]]);
						Material* mat = new Material(&BRDF(Color(diffuse[0], diffuse[1], diffuse[2], 1),
							Color(specular[0], specular[1], specular[2], 1), Color(ambient[0], ambient[1], ambient[2], 1), Color(mirror[0], mirror[1], mirror[2], 1), Color(emission[0], emission[1], emission[2], 1), shiness));
						primitives.push_back(make_shared<GeometricPrimitive>(tri, mat,transfstack.top()));
					}
				}
				else if (cmd == "pushTransform")
				{
					transfstack.push(transfstack.top());
				}
				else if (cmd == "popTransform"){
					if (transfstack.size() <= 1) {
						cerr << "Stack has no elements.  Cannot Pop\n";
					}
					else {
						transfstack.pop();
					}
				}
				else if (cmd == "translate"){
					validinput = readvals(s, 3, values);
					if (validinput)
					{
						Matrix trans = Matrix::translation(Vector3(values[0], values[1], values[2]));
						rightmultiply(trans, transfstack);
					}
				}
				else if (cmd == "scale"){
					validinput = readvals(s, 3, values);
					if (validinput)
					{
						Matrix scale = Matrix::scale(Vector3(values[0], values[1], values[2]));
						rightmultiply(scale,transfstack);
					}
				}
				else if (cmd == "rotate")
				{
					validinput = readvals(s, 4, values);
					if (validinput)
					{
						Matrix rotate = Matrix::rotation(Vector3(values[0] * values[3], values[1] * values[3], values[2] * values[3]));
						rightmultiply(rotate, transfstack);
					}
				}
				else if (cmd == "directional"){
					validinput = readvals(s, 6, values);
					if (validinput)
					{
						auto dl = make_shared<DLight>(Vector3(values[0], values[1], values[2]), Color(values[3], values[4], values[5]));
						lights.push_back(dl);
					}
				}
				else if (cmd == "point"){
					validinput = readvals(s, 6, values);
					if (validinput)
					{
						auto dl = make_shared<PLight>(Vector3(values[0], values[1], values[2]), Color(values[3], values[4], values[5]));
						lights.push_back(dl);
					}
				}
				else if (cmd == "ambient")
				{
					validinput = readvals(s, 3, values);
					if (validinput)
					{
						for (int i = 0; i < 3; i++)
						{
							ambient[i] = values[i];
						}
					}
				}
				else if (cmd == "diffuse")
				{
					validinput = readvals(s, 3, values);
					if (validinput)
					{
						for (int i = 0; i < 3; i++)
						{
							diffuse[i] = values[i];
						}
					}
				}
				else if (cmd == "specular")
				{
					validinput = readvals(s, 3, values);
					if (validinput)
					{
						for (int i = 0; i < 3; i++)
						{
							specular[i] = values[i];
						}
						for (int i = 0; i < 3; i++)
						{
							mirror[i] = values[i];
						}
					}
				}
				else if (cmd == "shininess")
				{
					validinput = readvals(s, 1, values);
					if (validinput)
					{
						shiness = values[0];
					}
				}
				else if (cmd == "emission")
				{
					validinput = readvals(s, 3, values);
					if (validinput)
					{
						for (int i = 0; i < 3; i++)
						{
							emission[i] = values[i];
						}
					}
				}
				else if (cmd == "mirror")
				{
					validinput = readvals(s, 3, values);
					if (validinput)
					{
						for (int i = 0; i < 3; i++)
						{
							mirror[i] = values[i];
						}
					}
				}
			}
			getline(in, str);
		}
	}
}