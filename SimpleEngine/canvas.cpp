#include"canvas.h"
#include<cmath>
void Canvas::drawPoint(const Vector2 &point, const Color &color)
{
	if (point.x >=0 && point.y >=0 &&
		point.x<_width && point.y <_height)
	{
		putPixel(point.x,point.y,color);
	}
}
void Canvas::drawLine(const Vertex2 &v1, const Vertex2 &v2)
{
	int x1 = v1.position.x;
	int y1 = v1.position.y;
	int x2 = v2.position.x;
	int y2 = v2.position.y;
	int dx = x2 - x1; int dy = y2 - y1;
	if (abs(dx) > abs(dy))
	{
		int sign = x2 - x1 > 0 ? 1 : -1;
		float ratio = 0;
		if (dx != 0)
		{
			ratio = (float)dy / dx;
		}
		for (int x = x1; x != x2; x++)
		{
			int y = y1 + (x - x1)*ratio;
			Color c = v1.color + ((v2.color - v1.color) * ((float)(x - x1) / (x2 - x1)));
			drawPoint(Vector2(x,y),c);
		}
	}
	else{
		int sign = y2 - y1 > 0 ? 1 : -1;
		float ratio = 0;
		if (dy != 0) {
			ratio = (float)dx / dy;
		}
		for (int y = y1; y != y2; y += sign) {
			int x = x1 + (y - y1) * ratio;
			Color c = v1.color + ((v2.color - v1.color) * ((float)(y - y1) / (y2 - y1)));
			drawPoint(Vector2(x, y), c);
		}
	}
}
void Canvas::drawTriangle(const Vertex2 &v1, const Vertex2 &v2, const Vertex2 &v3)
{
	int maxX =ceil(v1.position.x > v2.position.x ? (v1.position.x > v3.position.x ? v1.position.x : v3.position.x) : (v2.position.x>v3.position.x ? v2.position.x:v3.position.x));
	int minX = floor(v1.position.x < v2.position.x ? (v1.position.x < v3.position.x ? v1.position.x : v3.position.x) : (v2.position.x<v3.position.x ? v2.position.x : v3.position.x));
	int maxY = ceil(v1.position.y > v2.position.y ? (v1.position.y > v3.position.y ? v1.position.y : v3.position.y) : (v2.position.y>v3.position.y ? v2.position.y : v3.position.y));
	int minY = floor(v1.position.y < v2.position.y ? (v1.position.y < v3.position.y ? v1.position.y : v3.position.y) : (v2.position.y<v3.position.y ? v2.position.y : v3.position.y));
	float t01 = (v1.position.y - v2.position.y)*v3.position.x + (v2.position.x - v1.position.x)*v3.position.y + v1.position.x*v2.position.y - v2.position.x*v1.position.y;
	float t12 = (v2.position.y - v3.position.y)*v1.position.x + (v3.position.x - v2.position.x)*v1.position.y + v2.position.x*v3.position.y - v3.position.x*v2.position.y;
	float t20 = (v3.position.y - v1.position.y)*v2.position.x + (v1.position.x - v3.position.x)*v2.position.y + v3.position.x*v1.position.y - v1.position.x*v3.position.y;
	for (int y = minY; y != maxY; y++)
	{
		for (int x = minX; x != maxX; x++)
		{
			float a = ((v2.position.y - v3.position.y)*x + (v3.position.x - v2.position.x)*y + v2.position.x*v3.position.y - v3.position.x*v2.position.y) / t12;
			float b = ((v3.position.y - v1.position.y)*x + (v1.position.x - v3.position.x)*y + v3.position.x*v1.position.y - v1.position.x*v3.position.y)/t20;
			float c = ((v1.position.y - v2.position.y)*x + (v2.position.x - v1.position.x)*y + v1.position.x*v2.position.y - v2.position.x*v1.position.y)/t01;
			if (a >0 && b >0 && c > 0)
			{
				Color c = v1.color*a + v2.color*b + v3.color * 3;
				drawPoint(Vector2(x,y),c);
			}
		}
	}
}
void Canvas::putPixel(int x, int y, const Color &color)
{
	int index = int(_width*y + x);
	_pixels[index] = color.uint32();
}
void Canvas::loadImage(Image &image, Vector2 &position)
{
	int width = image.width;
	int height = image.height;
	for (int i = 0; i != height; i++)
	{
		for (int j = 0; j != width; j++)
		{
			int index = int((height+position.x)*i+width+j);
			_pixels[index] = image.pixels[i*width+j];
		}
	}
}
