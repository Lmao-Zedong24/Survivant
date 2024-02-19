#pragma once
#include "SurvivantRendering/Core/VertexAttributes.h"
#include "SurvivantRendering/Core/Buffers/VertexBuffer.h"
#include "SurvivantRendering/Core/Buffers/IndexBuffer.h"
#include "SurvivantCore/Resources/IResource.h"

#include <vector>
#include <string>

struct aiNode; 
struct aiScene;
struct aiMesh;

namespace SvRendering::Resources
{
    class Model: public SvCore::Resources::IResource
    {
    public:

        Model() = default;

        ~Model() = default;

        bool						Load(const std::string& p_filename) override;

        bool						Init() override;

        void						Bind() const;

        uint32_t					GetIndexCount() const;

    private:
        std::vector<Core::Vertex>	m_vertices;
        std::vector<uint32_t>		m_indices;

        Core::VertexAttributes		m_vao;
        Core::Buffers::VertexBuffer	m_vbo;
        Core::Buffers::IndexBuffer	m_ebo;

        void						ProcessNode(aiNode* node, const aiScene* scene);

        void						ProcessMesh(aiMesh* mesh);

    };
}