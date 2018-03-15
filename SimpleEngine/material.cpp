#include "material.h"

Material::Material()
	:empty_flag_(true), is_loaded_(false)
{
}

Material::Material(std::string file_path)
{

}

Material::~Material()
{
}

Color Material::getColor(const float u, const float v)
{
	if (empty_flag_)
	{
		return Color(0,0,0);
	}
	else 
	{
		if (is_loaded_)
		{
			return texture_.getColor(u, v);
		}
		return constantBRDF.ka + constantBRDF.emission;
	}
}
