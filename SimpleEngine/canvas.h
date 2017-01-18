#ifndef CANVAS_H_
#define CANVAS_H_
#include <cstdint>
#include"vector.h"
#include"vertex.h"
#include"color.h"
#include "image.h"
#include"foundation.h"
class Canvas{
public:
	Canvas(uint32_t *pixels, float width, float height){
		_pixels = pixels;
		_width = width;
		_height = height;
	}
	void drawPoint(const Vector2 &point,const Color &color);
	void drawLine(const Vertex2 &v1,const Vertex2 &v2);
	void drawTriangle(const Vertex2 &v1, const Vertex2 &v2, const Vertex2 &v3);
	void loadImage(Image &image,Vector2 &position);
private:
	void putPixel(int x,int y,const Color &color);
private:
	uint32_t *_pixels;
	float _width;
	float _height;
};

#endif