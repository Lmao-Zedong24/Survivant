#include "SurvivantRendering/Resources/Model.h"

#include <SurvivantCore/Debug/Assertion.h>
#include <SurvivantCore/Debug/Logger.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace LibMath;
using namespace SvRendering::Geometry;

namespace SvRendering::Resources
{
    Model::Model()
        : Model(std::vector<Mesh>())
    {
    }

    Model::Model(std::vector<Mesh> p_meshes)
        : m_meshes(std::move(p_meshes))
    {
        m_boundingBox =
        {
            Vector3(std::numeric_limits<float>::max()),
            Vector3(std::numeric_limits<float>::lowest())
        };

        for (const Mesh& mesh : m_meshes)
        {
            m_boundingBox.m_min = min(m_boundingBox.m_min, mesh.GetBoundingBox().m_min);
            m_boundingBox.m_max = max(m_boundingBox.m_max, mesh.GetBoundingBox().m_max);
        }
    }

    bool Model::Load(const std::string& p_path)
    {
        Assimp::Importer importer;
        importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE,
            aiPrimitiveType_POINT | aiPrimitiveType_LINE | aiPrimitiveType_POLYGON);

        const aiScene* scene = importer.ReadFile(p_path.c_str(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices
            | aiProcess_SortByPType | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph | aiProcess_RemoveRedundantMaterials
            | aiProcess_ImproveCacheLocality | aiProcess_GenUVCoords | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

        if (!CHECK(scene && scene->HasMeshes(), "Unable to load model from path \"%s\"", p_path.c_str()))
            return false;

        m_meshes.clear();
        m_meshes.reserve(scene->mNumMeshes);

        m_boundingBox =
        {
            Vector3(std::numeric_limits<float>::max()),
            Vector3(std::numeric_limits<float>::lowest())
        };

        // Ensure assimp vec3s are compatible with ours so we can safely convert from one to the other
        static_assert(sizeof(aiVector3D) == sizeof(Vector3));
        static_assert(
            offsetof(aiVector3D, x) == offsetof(Vector3, m_x) &&
            offsetof(aiVector3D, y) == offsetof(Vector3, m_y) &&
            offsetof(aiVector3D, z) == offsetof(Vector3, m_z)
        );

        for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
        {
            const aiMesh* mesh = scene->mMeshes[i];

            if (!mesh || mesh->mNumVertices == 0)
                continue;

            std::vector<Vertex> vertices;
            vertices.reserve(vertices.size() + mesh->mNumVertices);

            for (unsigned int idx = 0; idx < mesh->mNumVertices; ++idx)
            {
                const Vector3    position  = *reinterpret_cast<Vector3*>(&mesh->mVertices[idx]);
                const Vector3    normal    = mesh->mNormals ? *reinterpret_cast<Vector3*>(&mesh->mNormals[idx]) : Vector3(0);
                const aiVector3D uv        = mesh->mTextureCoords[0] ? mesh->mTextureCoords[0][idx] : aiVector3D(0);
                const Vector3    tangent   = mesh->mTangents ? *reinterpret_cast<Vector3*>(&mesh->mTangents[idx]) : Vector3(0);
                const Vector3    bitangent = mesh->mBitangents ? *reinterpret_cast<Vector3*>(&mesh->mBitangents[idx]) : Vector3(0);

                vertices.emplace_back(position, normal, Vector2(uv.x, uv.y), tangent, bitangent);
            }

            std::vector<uint32_t> indices;
            indices.reserve(static_cast<size_t>(mesh->mNumFaces) * 3);
            for (unsigned int faceIdx = 0; faceIdx < mesh->mNumFaces; ++faceIdx)
            {
                const aiFace face = mesh->mFaces[faceIdx];

                indices.push_back(face.mIndices[0]);
                indices.push_back(face.mIndices[1]);
                indices.push_back(face.mIndices[2]);
            }

            const Mesh& newMesh = m_meshes.emplace_back(vertices, indices);
            m_boundingBox.m_min = min(m_boundingBox.m_min, newMesh.GetBoundingBox().m_min);
            m_boundingBox.m_max = max(m_boundingBox.m_max, newMesh.GetBoundingBox().m_max);
        }

        return true;
    }

    bool Model::Init()
    {
        for (auto& mesh : m_meshes)
        {
            if (!mesh.Init())
                return false;
        }

        return true;
    }

    const Mesh& Model::GetMesh(const size_t p_index) const
    {
        ASSERT(p_index < m_meshes.size());
        return m_meshes[p_index];
    }

    size_t Model::GetMeshCount() const
    {
        return m_meshes.size();
    }

    BoundingBox Model::GetBoundingBox() const
    {
        return m_boundingBox;
    }
}
