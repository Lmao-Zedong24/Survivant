#include "SurvivantRendering/Core/Buffers/UniformBuffer.h"

#include "SurvivantRendering/RHI/OpenGL/OpenGLAPI.h"

#include <glad/gl.h>

using namespace SvRendering::Enums;
using namespace SvRendering::RHI;

namespace SvRendering::Core::Buffers
{
    UniformBuffer::UniformBuffer(const EAccessMode p_accessSpecifier, const uint32_t p_bindIndex)
        : m_bindIndex(p_bindIndex), m_accessSpecifier(p_accessSpecifier)
    {
        glGenBuffers(1, &m_id);
    }

    UniformBuffer::UniformBuffer(UniformBuffer&& p_other) noexcept
        : m_id(p_other.m_id), m_bindIndex(p_other.m_bindIndex), m_accessSpecifier(p_other.m_accessSpecifier)
    {
        p_other.m_id = 0;
    }

    UniformBuffer::~UniformBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    UniformBuffer& UniformBuffer::operator=(UniformBuffer&& p_other) noexcept
    {
        if (this == &p_other)
            return *this;

        glDeleteBuffers(1, &m_id);

        m_id              = p_other.m_id;
        m_bindIndex       = p_other.m_bindIndex;
        m_accessSpecifier = p_other.m_accessSpecifier;

        p_other.m_id        = 0;
        p_other.m_bindIndex = 0;

        return *this;
    }

    void UniformBuffer::SetBindIndex(const uint32_t p_bindIndex)
    {
        m_bindIndex = p_bindIndex;
    }

    void UniformBuffer::Bind(const uint32_t p_bindIndex)
    {
        SetBindIndex(p_bindIndex);
        Bind();
    }

    void UniformBuffer::Bind() const
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, m_bindIndex, m_id);
    }

    void UniformBuffer::Unbind() const
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, m_bindIndex, 0);
    }

    void UniformBuffer::SetRawData(const void* p_data, const size_t p_size) const
    {
        glBindBuffer(GL_UNIFORM_BUFFER, m_id);
        glBufferData(GL_UNIFORM_BUFFER, static_cast<GLsizeiptr>(p_size), p_data, OpenGLAPI::ToGLEnum(m_accessSpecifier));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void UniformBuffer::SetRawSubData(const void* p_data, const size_t p_size, const intptr_t p_offset) const
    {
        glBindBuffer(GL_UNIFORM_BUFFER, m_id);
        glBufferSubData(GL_UNIFORM_BUFFER, p_offset, static_cast<GLsizeiptr>(p_size), p_data);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
}
