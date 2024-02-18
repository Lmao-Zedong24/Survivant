#include "SurvivantRendering/Resources/Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

bool Model::Load(const std::string& p_filename)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(p_filename, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		// Error handling if the model file cannot be loaded
		std::cerr << "Error: " << importer.GetErrorString() << std::endl;
		return false;
	}

	// Process all nodes recursively
	ProcessNode(scene->mRootNode, scene);

	return true;
}

bool Model::Init()
{

}


void Model::SetMaterial()
{

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
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
		Vertex vertex;
		// Fill in vertex data (position, normal, texture coordinates)
		vertex.x = mesh->mVertices[i].x;
		vertex.y = mesh->mVertices[i].y;
		vertex.z = mesh->mVertices[i].z;
		vertex.nx = mesh->mNormals[i].x;
		vertex.ny = mesh->mNormals[i].y;
		vertex.nz = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0] != nullptr && i < mesh->mNumVertices) {
			// Check if the mesh has texture coordinates and if the index i is within bounds
			if (mesh->mTextureCoords[0][i] != nullptr) 
			{
				// Check if texture coordinates are available for this vertex
				vertex.u = mesh->mTextureCoords[0][i].x;
				vertex.v = mesh->mTextureCoords[0][i].y;
			}
			else {
				vertex.u = 0.0f;
				vertex.v = 0.0f;
			}
		}
		else
		{
			vertex.u = 0.0f;
			vertex.v = 0.0f;
		}
		m_vertices.push_back(vertex);
	}

	// Process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j) {
			m_indices.push_back(face.mIndices[j]);
		}
	}
}
