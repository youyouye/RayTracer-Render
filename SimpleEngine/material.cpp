#include "material.h"

Material::Material()
	:empty_flag_(true), is_loaded_(false)
{
	default_color_ = Color(0.5,0.5,0.5);
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
		return default_color_;
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
