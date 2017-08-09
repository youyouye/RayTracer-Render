#ifndef BRDF_H_
#define BRDF_H_
#include "color.h"
#include "Texture.h"
#include <memory>
class BRDF
{
public:
	BRDF();
	BRDF(Color &d,Color &s,Color &a,Color &r){
		this->kd = d;
		this->ks = s;
		this->kr = r;
		this->ka = a;
	};
	BRDF(Color &d, Color &s, Color &a, Color &r,Color &emission,float shin){
		this->kd = d;
		this->ks = s;
		this->kr = r;
		this->ka = a;
		this->emission = emission;
		this->shininess = shin;
	}
	~BRDF();
	virtual void setTexture(std::shared_ptr<Texture> tex) {}
public:
	// kd, ks, ka are diffuse, specular and ambient component respectively
	// kr is the mirror reflection coefficient
	Color kd, ks, ka, kr;
	float shininess;
	Color emission;
};

class TextureBRDF : public BRDF{
public:
	TextureBRDF(Color &d, Color &s, Color &a, Color &r):BRDF(d,s,a,r){}
	TextureBRDF(Color &d, Color &s, Color &a, Color &r, Color &emission, float shin) 
		:BRDF(d,s,a,r,emission,shin)
	{}
	virtual void setTexture(std::shared_ptr<Texture> tex) {
		this->texture = tex;
	}
public:
	std::shared_ptr<Texture> texture;
};

#endif