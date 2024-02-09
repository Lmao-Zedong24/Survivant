#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/gl.h>
#include "SurvivantRendering/Resources/Model.h"
#include "Matrix/Matrix4.h"
#include "Vector/Vector3.h"

bool Model::LoadModel(const std::string& p_filename)
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

void Model::SetTransformation(float p_x, float p_y, float p_z, float p_rotationX,
							  float p_rotationY, float p_rotationZ, float p_scaleX,
							  float p_scaleY, float p_scaleZ)
{
	// Create transformation matrices for translation, rotation, and scaling
	LibMath::Matrix4 translationMatrix = LibMath::translation(LibMath::Vector3(p_x, p_y, p_z));
	LibMath::Matrix4 rotationMatrixX = LibMath::rotation(LibMath::Radian(p_rotationX), LibMath::Vector3(1.0f, 0.0f, 0.0f));
	LibMath::Matrix4 rotationMatrixY = LibMath::rotation(LibMath::Radian(p_rotationY), LibMath::Vector3(0.0f, 1.0f, 0.0f));
	LibMath::Matrix4 rotationMatrixZ = LibMath::rotation(LibMath::Radian(p_rotationZ), LibMath::Vector3(0.0f, 0.0f, 1.0f));
	LibMath::Matrix4 scalingMatrix = LibMath::scaling(LibMath::Vector3(p_scaleX, p_scaleY, p_scaleZ));

	// Combine the transformation matrices to get the final transformation matrix
	m_transformationMatrix = translationMatrix * rotationMatrixX * rotationMatrixY * rotationMatrixZ * scalingMatrix;
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
	// Clear vectors to release memory
	m_vertices.clear();
	m_normals.clear();
	m_UVs.clear();
	m_indices.clear();

	// Reset transformation parameters
	m_x = m_y = m_z = 0.0f;
	m_rotationX = m_rotationY = m_rotationZ = 0.0f;
	m_scaleX = m_scaleY = m_scaleZ = 1.0f;
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	// Process all meshes in this node
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene);
	}

	// Process all child nodes
	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

void Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	// Process vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		// Fill in vertex data (position, normal, texture coordinates)
		// You'll need to adjust this according to Assimp's vertex data structure
		// For example:
		vertex.x = mesh->mVertices[i].x;
		vertex.y = mesh->mVertices[i].y;
		vertex.z = mesh->mVertices[i].z;
		vertex.nx = mesh->mNormals[i].x;
		vertex.ny = mesh->mNormals[i].y;
		vertex.nz = mesh->mNormals[i].z;	
		if (mesh->mTextureCoords[0]) // Check if the mesh has texture coordinates
		{
			vertex.u = mesh->mTextureCoords[0][i].x;
			vertex.v = mesh->mTextureCoords[0][i].y;
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
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
		{
			m_indices.push_back(face.mIndices[j]);
		}
	}
}
