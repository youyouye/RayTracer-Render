#include "ImageTexture.h"
#include "Ray.h"
#include "Mapping.h"
#include "image.h"
#include "Primitive.h"
ImageTexture::ImageTexture()
{
}


ImageTexture::~ImageTexture()
{
}
Color ImageTexture::getColor(Intersection& instersect) const
{
	int row, column;
	if (mappingPtr)
	{
		mappingPtr->getPixelCoordinates(instersect.localGeo.pos-instersect.primitive->getSpecialVec(),imagePtr->width,imagePtr->height,row,column);
	}
	else{
		row = (int)(0.5*(vres - 1));
		row = (int)(0.5*(hres - 1));
	}
	return imagePtr->getPixelColor(row,column);
}
