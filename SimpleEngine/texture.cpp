#include "texture.h"

ImageTexture::ImageTexture()
	:image_("")
{
	//TODO:�ĳɼӸ��������ô��;
}

void ImageTexture::setColor(const Color& color)
{

}

Color ImageTexture::getColor(Vector3 &point)
{

}

Color ImageTexture::getColor(double u, double v)
{
	int x = std::fmod(std::fabs(u), 1.0) * (image_.width - 1);
	int y = std::fmod(std::fabs(v), 1.0) * (image_.height -1);


}