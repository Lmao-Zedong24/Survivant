#include "SurvivantRendering/Resources/Model.h"
#include "SurvivantCore/Debug/Logger.h"
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
        SV_LOG_ERROR("The model file cannot be loaded");
		return false;
	}

	// Process all nodes recursively
	ProcessNode(scene->mRootNode, scene);

	return true;
}

bool Model::Init()
{
    // Generate Vertex Array Object (VAO)
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Generate Vertex Buffer Object (VBO)
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    // Specify vertex attribute pointers
    glEnableVertexAttribArray(0); // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));
    glEnableVertexAttribArray(1); // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, nx));
    glEnableVertexAttribArray(2); // Texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u));

    // Generate Element Buffer Object (EBO)
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

    // Unbind VAO to prevent unintended modification
    glBindVertexArray(0);

    // Check for OpenGL errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) 
    {
        return false;
    }

    return true; // Initialization successful
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

void Model::ProcessMesh(aiMesh* mesh) {
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

        // Check if the mesh has texture coordinates and if the index i is within bounds
        if (mesh->mTextureCoords[0] && i < mesh->mNumVertices) {
            if (mesh->mTextureCoords[0][i].x != 0.0f || mesh->mTextureCoords[0][i].y != 0.0f) {
                vertex.u = mesh->mTextureCoords[0][i].x;
                vertex.v = mesh->mTextureCoords[0][i].y;
            }
            else {
                vertex.u = 0.0f;
                vertex.v = 0.0f;
            }
        }
        else {
            vertex.u = 0.0f;
            vertex.v = 0.0f;
        }
        m_vertices.push_back(vertex);
    }

    // Process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            m_indices.push_back(face.mIndices[j]);
        }
    }
}



