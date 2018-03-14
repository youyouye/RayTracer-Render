#pragma once
#include <vector>
#include "color.h"
#include "vector.h"
#include "image.h"

class Texture 
{
public:
	Texture() {}
	virtual	~Texture() {}
	virtual Color getColor(const float& u, const float& v) { return Color(); }
};

class ImageTexture : public Texture 
{
public:
	ImageTexture();
	void setColor(const Color& color);
	virtual Color getColor(const float& u,const float& v) override;

private:
	std::vector<unsigned char> image;
	unsigned int width;
	unsigned int height;
	Color color_;
};
