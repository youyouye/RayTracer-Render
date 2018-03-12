#pragma once
#include <vector>
#include "color.h"
#include "vector.h"
#include "image.h"

class Texture 
{
public:
	virtual	~Texture() {}
	virtual Color getColor(Vector3 &point) = 0;
	virtual Color getColor(double u,double v) = 0;
};

class ImageTexture : public Texture 
{
public:
	ImageTexture();
	void setColor(const Color& color);

	virtual Color getColor(Vector3 &point) override;
	virtual Color getColor(double u, double v) override;

private:
	std::vector<unsigned char> image;
	unsigned int width;
	unsigned int height;
	Color color_;
};
