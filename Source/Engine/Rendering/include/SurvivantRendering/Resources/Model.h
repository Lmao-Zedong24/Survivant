#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/gl.h>
#include "Matrix/Matrix4.h"
#include "Vector/Vector3.h"
#include "SurvivantRendering/Resources/texture.h"
#include "SurvivantCore/Resources/IResource.h"

struct aiNode; 
struct aiScene;
struct aiMesh;

struct Vertex
{
	float			x, y, z;
	float			nx, ny, nz;
	float			u, v;
};

class Model: public SvCore::Resources::IResource
{
public:
	Model();

	~Model();

	virtual bool						Load(const std::string& p_filename) override;

	virtual bool						Init() override;
	
	void								SetMaterial();

private:

	void								ProcessNode(aiNode* node, const aiScene* scene);

	void								ProcessMesh(aiMesh* mesh);

	std::vector<Vertex>					m_vertices;
	std::vector<Vertex>					m_normals;
	std::vector<Vertex>					m_UVs;
	std::vector<unsigned int>			m_indices;
	LibMath::Matrix4					m_transformationMatrix;
	GLuint								m_vao;
	GLuint								m_vbo; 
	GLuint								m_ebo;
	float								m_x, m_y, m_z;
	float								m_rotationX, m_rotationY, m_rotationZ;
	float								m_scaleX, m_scaleY, m_scaleZ;

	
};