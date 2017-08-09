#include "Texture.h"
#include "Ray.h"

Texture::Texture()
{
}
Texture::~Texture(){
	delete imagePtr;
	delete mappingPtr;
}