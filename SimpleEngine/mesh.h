#pragma once
#include <vector>
#include "Primitive.h"
#include "light.h"
#include "tiny_obj_loader/tiny_obj_loader.h"
#include "material.h"

class Mesh 
{
public:
	Mesh(const std::string& file_path);
	~Mesh() = default;
	std::vector<std::shared_ptr<Primitive>> getPrimitives();
	std::vector<std::shared_ptr<Light>> getLights();
private:
	std::vector<tinyobj::shape_t> m_shapes_;
	std::vector<tinyobj::material_t> m_materials_;
	std::vector<std::shared_ptr<Primitive>> tris_;
	std::vector<Material> materials_;
	Vector3 position_;
};