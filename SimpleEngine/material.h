#ifndef MATERIAL_H_
#define MATERIAL_H_
#include "BRDF.h"
#include "vector.h"
#include "texture.h"

enum MaterialType
{
	SEPCULAR = 1,
	DIFFUSE,
	EMIT,
};

class Material
{
public:
	Material();
	Material(MaterialType type,Color default_color) : 
		default_color_(default_color),empty_flag_(true),is_loaded_(false),material_type_(type)
	{
	}
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
	Color default_color_;
	bool empty_flag_;
	bool is_loaded_;
	BRDF constantBRDF;
	Texture texture_;
	MaterialType material_type_;
};


#endif