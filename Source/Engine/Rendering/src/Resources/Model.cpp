#include "SurvivantRendering/Resources/Model.h"

#include <SurvivantCore/Debug/Assertion.h>
#include <SurvivantCore/Debug/Logger.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace SvRendering::Core;
using namespace SvRendering::Core::Buffers;

namespace SvRendering::Resources
{
	bool Model::Load(const std::string& p_filename)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(p_filename, aiProcess_Triangulate | aiProcess_MakeLeftHanded);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			SV_LOG_ERROR("The model file cannot be loaded");
			return false;
		}

		// Process all nodes recursively
		ProcessNode(scene->mRootNode, scene);

		return true;
	}

	bool Model::Init()
	{
		// Generate Vertex Buffer Object (VBO)
		m_vbo = VertexBuffer(m_vertices);

		// Generate Element Buffer Object (EBO)
		m_ebo = IndexBuffer(m_indices);

		// Generate Vertex Array Object (VAO)
		m_vao = VertexAttributes(m_vbo, m_ebo);

		return true; // Initialization successful
	}

	void Model::Bind() const
	{
		m_vao.Bind();
	}

	uint32_t Model::GetIndexCount() const
	{
		return static_cast<uint32_t>(m_indices.size());
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		// Process all meshes in this node
		for (unsigned int i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			ProcessMesh(mesh);
		}

		// Process all child nodes
		for (unsigned int i = 0; i < node->mNumChildren; ++i)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	void Model::ProcessMesh(aiMesh* mesh)
	{
		// Process vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
		{
			Vertex vertex;

			// Fill in vertex data (position, normal, texture coordinates)
			vertex.m_position.m_x = mesh->mVertices[i].x;
			vertex.m_position.m_y = mesh->mVertices[i].y;
			vertex.m_position.m_z = mesh->mVertices[i].z;

			// Check if the mesh has normals
			if (mesh->mNormals)
			{
				vertex.m_normal.m_x = mesh->mNormals[i].x;
				vertex.m_normal.m_y = mesh->mNormals[i].y;
				vertex.m_normal.m_z = mesh->mNormals[i].z;
			}

			// Check if the mesh has texture coordinates
			if (mesh->mTextureCoords[0])
			{
				vertex.m_textureUV.m_x = mesh->mTextureCoords[0][i].x;
				vertex.m_textureUV.m_y = mesh->mTextureCoords[0][i].y;
			}

			m_vertices.push_back(vertex);
		}

		// Process indices
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
		{
			aiFace face = mesh->mFaces[i];

			ASSERT(face.mNumIndices == 3, "Meshes should be triangulated");

			for (unsigned int j = 0; j < face.mNumIndices; ++j)
			{
				m_indices.push_back(face.mIndices[j]);
			}
		}
	}
}



