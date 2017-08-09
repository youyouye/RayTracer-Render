#ifndef TEXTURE_H_
#define TEXTURE_H_
#include "color.h"
class Image;
class Mapping;
class Intersection;
class Texture
{
public:
	Texture();
	~Texture();
	virtual Color getColor(Intersection& interset) const = 0;
	Image* imagePtr;
	Mapping* mappingPtr;
};

#endif