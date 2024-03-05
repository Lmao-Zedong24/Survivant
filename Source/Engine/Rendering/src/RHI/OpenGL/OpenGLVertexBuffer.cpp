#include "SurvivantRendering/RHI/OpenGL/OpenGLVertexBuffer.h"

#include <glad/gl.h>

using namespace SvRendering::Geometry;

namespace SvRendering::RHI
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(const Vertex* p_vertices, const uint32_t p_count)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, p_count * static_cast<GLsizeiptr>(sizeof(Vertex)), p_vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(OpenGLVertexBuffer&& p_other) noexcept
        : IVertexBuffer(std::forward<IVertexBuffer&&>(p_other)), m_id(p_other.m_id)
    {
        p_other.m_id = 0;
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    OpenGLVertexBuffer& OpenGLVertexBuffer::operator=(OpenGLVertexBuffer&& p_other) noexcept
    {
        if (&p_other == this)
            return *this;

        glDeleteBuffers(1, &m_id);

        m_id       = p_other.m_id;
        p_other.m_id = 0;

        IVertexBuffer::operator=(std::move(p_other));

        return *this;
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
