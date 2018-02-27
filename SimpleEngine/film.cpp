#include "film.h"
#include "FreeImage.h"
#include <string>
#include <iostream>
using namespace std;

void Film::commit(Sample& sample, Color& color){
	int index = (sample.y*width + sample.x);
	pixels[index] = color.uint32();
}
void Film::writeImage(){

	FIBITMAP* bitmap = FreeImage_Allocate(width, height, 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
	int bytespp = FreeImage_GetLine(bitmap) / FreeImage_GetWidth(bitmap);
	for (unsigned i = 0; i < FreeImage_GetHeight(bitmap); i++)
	{
		BYTE* bits = FreeImage_GetScanLine(bitmap,i);
		for (unsigned j = 0; j < FreeImage_GetWidth(bitmap); j++)
		{
			int temp = height-i;
			BYTE t1 = ((pixels[temp*width + j] & FI_RGBA_RED_MASK) >> 16);
			BYTE t2 = ((pixels[temp*width + j] & FI_RGBA_GREEN_MASK) >> 8);
			BYTE t3 = ((pixels[temp*width + j] & FI_RGBA_BLUE_MASK));
			BYTE t4 = ((pixels[temp*width + j] & FI_RGBA_ALPHA_MASK >> 24));
			bits[FI_RGBA_RED] = t1;
			bits[FI_RGBA_GREEN] = t2;
			bits[FI_RGBA_BLUE] = t3;
			bits[FI_RGBA_ALPHA] = 255;
			bits += bytespp;
		}
	}
	std::string filename = "..//test.png";
	FreeImage_Save(FIF_PNG,bitmap,filename.c_str(),0);

}
