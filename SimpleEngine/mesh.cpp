#include "mesh.h"
#include <iostream>
#include "Log.h"

Mesh::Mesh(const std::string& file_path) 
{
	std::string basepath;
	unsigned long pos = file_path.find_last_of("/");
	basepath = file_path.substr(0, pos + 1);
	std::string err = tinyobj::LoadObj(m_shapes_,m_materials_,file_path.c_str(),basepath.c_str());
	if (!err.empty())
	{
		LOG_ERROR << "load obj file fail!" << LOG_END;
		exit(1);
	}

	for (int i = 0;i < m_materials_.size();i++)
	{
		std::string texture_path = "";
		if (!m_materials_[i].diffuse_texname.empty())
		{
			if (m_materials_[i].diffuse_texname[0] == '/')
			{
				texture_path = m_materials_[i].diffuse_texname;
			}
			texture_path = basepath + m_materials_[i].diffuse_texname;
			materials_.push_back(texture_path);
		}
		else 
		{
			materials_.push_back(Material());
		}
	}
	for (int i = 0;i < m_shapes_.size();i++)
	{
		long indices_size = m_shapes_[i].mesh.indices.size() / 3;
		//Triangle vertex
		Vector3 v0, v1, v2;
		for (size_t j = 0;j < indices_size;j++)
		{
			v0 = Vector3(
				m_shapes_[i].mesh.positions[m_shapes_[i].mesh.indices[3 * j] * 3],
				m_shapes_[i].mesh.positions[m_shapes_[i].mesh.indices[3 * j] * 3 + 1],
				m_shapes_[i].mesh.positions[m_shapes_[i].mesh.indices[3 * j] * 3 + 2]
			) + position_;
			v1 = Vector3(
				m_shapes_[i].mesh.positions[m_shapes_[i].mesh.indices[3 * j] * 3],
				m_shapes_[i].mesh.positions[m_shapes_[i].mesh.indices[3 * j] * 3 + 1],
				m_shapes_[i].mesh.positions[m_shapes_[i].mesh.indices[3 * j] * 3 + 2]
			) + position_;
			v2 = Vector3(
				m_shapes_[i].mesh.positions[m_shapes_[i].mesh.indices[3 * j] * 3],
				m_shapes_[i].mesh.positions[m_shapes_[i].mesh.indices[3 * j] * 3 + 1],
				m_shapes_[i].mesh.positions[m_shapes_[i].mesh.indices[3 * j] * 3 + 2]
			) + position_;

			Vector3 t0, t1, t2;
			//triangle texture coordinates
			if (m_shapes_[i].mesh.indices[3 * j + 2] * 2 + 1 < m_shapes_[i].mesh.texcoords.size())
			{
				t0 = Vector3(
					m_shapes_[i].mesh.texcoords[m_shapes_[i].mesh.indices[3 * j] * 2],
					m_shapes_[i].mesh.texcoords[m_shapes_[i].mesh.indices[3 * j] * 2 + 1],
					0
				);
				t1 = Vector3(
					m_shapes_[i].mesh.texcoords[m_shapes_[i].mesh.indices[3 * j + 1] * 2],
					m_shapes_[i].mesh.texcoords[m_shapes_[i].mesh.indices[3 * j + 1] * 2 + 1],
					0
				);
				t2 = Vector3(
					m_shapes_[i].mesh.texcoords[m_shapes_[i].mesh.indices[3 * j + 2] * 2],
					m_shapes_[i].mesh.texcoords[m_shapes_[i].mesh.indices[3 * j + 2] * 2 + 1],
					0
				);
			}
			else 
			{
				t0 = Vector3();
				t1 = Vector3();
				t2 = Vector3();
			}
			Triangle* shape = new Triangle(v0, v1, v2, t0, t1, t2);
			GeometricPrimitive* tri = new GeometricPrimitive();
			tri->shape = shape;
			if (m_shapes_[i].mesh.material_ids[j] < materials_.size())
			{
				tri->mat = &materials_[m_shapes_[i].mesh.material_ids[j]];
			}
			else 
			{
				tri->mat = new Material();
			}
		}
	}
	m_shapes_.clear();
	m_materials_.clear();
}