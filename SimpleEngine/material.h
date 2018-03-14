#ifndef MATERIAL_H_
#define MATERIAL_H_
#include "BRDF.h"
#include "vector.h"
#include "texture.h"

class Material
{
public:
	Material();
	Material(std::string file_path);
	Material(BRDF* brdf){
		this->constantBRDF = *brdf;
	}
	~Material();
	BRDF getBRDF(LocalGeo& local,BRDF* bref) const{
		return constantBRDF;
	}
	Color getColor(const float u, const float v) ;
public:
	bool empty_flag_;
	bool is_loaded_;
	BRDF constantBRDF;
	Texture texture_;
};


#endif