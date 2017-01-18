#ifndef IMAGE_H_
#define IMAGE_H_
#include<cstdint>
class Image{
public:
	uint32_t *pixels;
	int width;
	int height;
	Image(const char *path);
	virtual ~Image(){
		delete[]pixels;
	}
};


#endif