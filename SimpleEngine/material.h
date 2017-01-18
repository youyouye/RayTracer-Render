#ifndef MATERIAL_H_
#define MATERIAL_H_
#include "BRDF.h"
#include "vector.h"
class Material
{
public:
	Material();
	Material(BRDF* brdf){
		this->constantBRDF = *brdf;
	}
	~Material();
	BRDF getBRDF(LocalGeo& local,BRDF* bref) const{
		return constantBRDF;
	}
public:
	BRDF constantBRDF;
};


#endif