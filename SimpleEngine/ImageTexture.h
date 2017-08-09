#ifndef IMAGETEXTURE_H_
#define IMAGETEXTURE_H_
#include "Texture.h"
class Intersection;
class ImageTexture : public Texture
{
public:
	ImageTexture();
	~ImageTexture();
	virtual Color getColor(Intersection& intersect) const;
private:
	int hres;
	int vres;
	
};

#endif