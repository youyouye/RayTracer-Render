#include "material.h"

Material::Material()
	:empty_flag_(true), is_loaded_(false)
{
	default_color_ = Color(0.5,0.5,0.5);
}

Material::Material(MaterialType type,Color default_color) :
        default_color_(default_color),empty_flag_(true),is_loaded_(false),material_type_(type)
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
