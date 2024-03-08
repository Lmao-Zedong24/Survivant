#include "SurvivantRendering/Core/Buffers/VertexBuffer.h"

#include <glad/gl.h>

using namespace SvRendering::Geometry;

namespace SvRendering::Core::Buffers
{
    VertexBuffer::VertexBuffer(const Vertex* p_vertices, const intptr_t p_verticesCount)
    {
        glGenBuffers(1, &m_bufferIndex);
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferIndex);
        glBufferData(GL_ARRAY_BUFFER, p_verticesCount * static_cast<GLsizeiptr>(sizeof(Vertex)), p_vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::VertexBuffer(const std::vector<Vertex>& p_vertices)
        : VertexBuffer(p_vertices.data(), static_cast<intptr_t>(p_vertices.size()))
    {
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferIndex);
    }

    void VertexBuffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
