#ifndef IMAGE_H_
#define IMAGE_H_
#include<cstdint>
#include "color.h"
class FIBITMAP;

class Image{
public:
	uint32_t *pixels;
	int width;
	int height;
	Image(const char *path);
	virtual ~Image();
	Image(const char *path,int id);
	Color getPixelColor(unsigned x,unsigned y);
private:
	FIBITMAP* bitmap;
};


#endif