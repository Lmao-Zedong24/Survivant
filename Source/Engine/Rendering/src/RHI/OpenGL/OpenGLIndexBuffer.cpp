#include "SurvivantRendering/RHI/OpenGL/OpenGLIndexBuffer.h"

#include <glad/gl.h>

namespace SvRendering::RHI
{
    OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* p_indices, const uint32_t p_count)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_count * static_cast<GLsizeiptr>(sizeof(uint32_t)), p_indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(OpenGLIndexBuffer&& p_other) noexcept
        : IIndexBuffer(std::forward<IIndexBuffer&&>(p_other)), m_id(p_other.m_id)
    {
        p_other.m_id = 0;
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    OpenGLIndexBuffer& OpenGLIndexBuffer::operator=(OpenGLIndexBuffer&& p_other) noexcept
    {
        if (&p_other == this)
            return *this;

        glDeleteBuffers(1, &m_id);

        m_id       = p_other.m_id;
        p_other.m_id = 0;

        IIndexBuffer::operator=(std::move(p_other));

        return *this;
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
