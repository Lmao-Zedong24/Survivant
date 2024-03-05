#include "SurvivantRendering/Resources/Mesh.h"

using namespace LibMath;
using namespace SvRendering::RHI;
using namespace SvRendering::Geometry;

namespace SvRendering::Resources
{
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
        : m_vertices(std::move(vertices)), m_indices(std::move(indices))
    {
        m_boundingBox =
        {
            Vector3(std::numeric_limits<float>::max()),
            Vector3(std::numeric_limits<float>::lowest())
        };

        for (const Vertex& vertex : m_vertices)
        {
            m_boundingBox.m_min = min(m_boundingBox.m_min, vertex.m_position);
            m_boundingBox.m_max = max(m_boundingBox.m_max, vertex.m_position);
        }
    }

    Mesh::Mesh(const Mesh& other)
        : Mesh(other.m_vertices, other.m_indices)
    {
        Init();
    }

    Mesh& Mesh::operator=(const Mesh& other)
    {
        if (this == &other)
            return *this;

        m_vertices = other.m_vertices;
        m_indices  = other.m_indices;

        Init();

        return *this;
    }

    bool Mesh::Init()
    {
        m_vbo = IVertexBuffer::Create(m_vertices);
        m_ebo = IIndexBuffer::Create(m_indices);
        m_vao = IVertexArray::Create(*m_vbo, *m_ebo);

        return true;
    }

    void Mesh::Bind() const
    {
        m_vao->Bind();
        m_ebo->Bind();
        m_vbo->Bind();
    }

    void Mesh::Unbind() const
    {
        m_vao->Unbind();
    }

    uint32_t Mesh::GetIndexCount() const
    {
        return static_cast<uint32_t>(m_indices.size());
    }

    BoundingBox Mesh::GetBoundingBox() const
    {
        return m_boundingBox;
    }
}
