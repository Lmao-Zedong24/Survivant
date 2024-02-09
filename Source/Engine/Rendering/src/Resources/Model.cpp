#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/gl.h>
#include "SurvivantRendering/Resources/Model.h"


bool Model::LoadModel(const std::string& p_filename)
{
	std::ifstream file(p_filename);
	if (!file.is_open()) 
	{
		std::cerr << "Error: Unable to open file: " << p_filename << std::endl;
		return false;
	}

	std::string line;
	while (std::getline(file, line)) 
	{
		std::istringstream iss(line);
		std::string type;
		iss >> type;

		if (type == "v")
		{
			Vertex vertex;
			iss >> vertex.x >> vertex.y >> vertex.z;
			m_vertices.push_back(vertex);
		}
		else if (type == "vn")
		{
			float nx, ny, nz;
			iss >> nx >> ny >> nz;
			m_vertices.back().nx = nx;
			m_vertices.back().ny = ny;
			m_vertices.back().nz = nz;
		}
		else if (type == "vt")
		{
			float u, v;
			iss >> u >> v;
			m_vertices.back().u = u;
			m_vertices.back().v = v;
		}
	}

	file.close();
	std::cout <<"Model loaded successfully from file: "<< p_filename << std::endl;
	return true;
}

void Model::RenderModel()
{
	
}

void Model::SetTransformation(float p_x, float p_y, float p_z, float p_rotationX,
	float p_rotationY, float p_rotationZ, float p_scaleX,
	float p_scaleY, float p_scaleZ)
{

}

void Model::PlayAnimation(const std::string& p_animationName)
{

}

void Model::StopAnimation()
{

}

void Model::SetMaterial()
{

}

bool Model::CheckCollision()
{

}

void Model::Update(float p_deltatime)
{

}

void Model::CleanUp()
{

}