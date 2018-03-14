#include "texture.h"

ImageTexture::ImageTexture()
{
	//TODO:改成加个库或者怎么样;
}

void ImageTexture::setColor(const Color& color)
{

}

Color ImageTexture::getColor(const float& u, const float& v)
{
	int x = (fmod(fabs(u), 1.0)) * (width - 1);
	int y = (1. - fmod(fabs(v), 1.0)) * (height - 1);
	double r, g, b;
	r = (double)image.at(y*width * 4 + x * 4) / 255.;
	g = (double)image.at(y*width * 4 + x * 4 + 1) / 255.;
	b = (double)image.at(y*width * 4 + x * 4 + 2) / 255.;
	return Color(r, g, b);
}