#include <fstream>
#include <string>
#include <sstream>
#include "image.h"
#include "foundation.h"
#include "FreeImage.h"

Image::Image(const char *path)
{
	std::ifstream imageFile(path);
	std::string line;
	// eat file descriptor and version

	getline(imageFile, line);
	getline(imageFile, line);

	getline(imageFile, line);
	width = atoi(line.c_str());

	getline(imageFile, line);
	height = atoi(line.c_str());

	pixels = new uint32_t[width * height];
	
	const char delimiter = ' ';
	for (int i = 0; i < height; i++) {
		getline(imageFile, line);
		auto row = split(line, delimiter);
		for (int j = 0; j < width; j++) {
			std::stringstream s(row[j]);
			unsigned int pixel;
			s >> pixel;
			pixels[i * width + j] = pixel;
		}
	}
}
Image::Image(const char *path, int id){
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	fif = FreeImage_GetFileType(path,0);
	if (fif == FIF_UNKNOWN)
	{
		fif = FreeImage_GetFIFFromFilename(path);
	}
	if (fif != FIF_UNKNOWN && FreeImage_FIFSupportsReading(fif))
	{
		FIBITMAP *dib = FreeImage_Load(fif,path);
		if (dib)
		{
			width = FreeImage_GetWidth(dib);
			height = FreeImage_GetHeight(dib);
			this->bitmap = dib;
		}
	}
}
Image::~Image(){
	if (pixels)
		delete[]pixels;
	if (bitmap)
		delete bitmap;
}

Color Image::getPixelColor(unsigned x, unsigned y){
	if (bitmap)
	{
		RGBQUAD rgb;
		FreeImage_GetPixelColor(bitmap,x,y,&rgb);
		return Color(rgb.rgbRed/255.0f,rgb.rgbGreen/255.0f,rgb.rgbBlue/255.0f);
	}
	return Color();
}