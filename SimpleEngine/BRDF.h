#ifndef BRDF_H_
#define BRDF_H_
#include"color.h"

class Texture;

class BRDF
{
public:
	BRDF();
	BRDF(const Color &d,const Color &s,const Color &a,const Color &r){
		this->kd = d;
		this->ks = s;
		this->kr = r;
		this->ka = a;
	};
	BRDF(const Color &d,const Color &s,const Color &a,const Color &r,const Color &emission,float shin){
		this->kd = d;
		this->ks = s;
		this->kr = r;
		this->ka = a;
		this->emission = emission;
		this->shininess = shin;
	}
	~BRDF();

public:
	// kd, ks, ka are diffuse, specular and ambient component respectively
	// kr is the mirror reflection coefficient
	Color kd, ks, ka, kr;
	float shininess;
	Color emission;
};

class TextureBRDF : public BRDF
{
public:
private:
	Texture* texture_;
};





#endif
