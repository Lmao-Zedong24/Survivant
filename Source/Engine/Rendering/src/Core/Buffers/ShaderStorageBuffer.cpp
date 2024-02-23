#include "SurvivantRendering/Core/Buffers/ShaderStorageBuffer.h"

#include <glad/gl.h>

using namespace SvRendering::Enums;

namespace SvRendering::Core::Buffers
{
    GLenum ToGLEnum(const EAccessSpecifier p_accessSpecifier)
    {
        switch (p_accessSpecifier)
        {
        case EAccessSpecifier::STREAM_DRAW:
            return GL_STREAM_DRAW;
        case EAccessSpecifier::STREAM_READ:
            return GL_STREAM_READ;
        case EAccessSpecifier::STREAM_COPY:
            return GL_STREAM_COPY;
        case EAccessSpecifier::DYNAMIC_DRAW:
            return GL_DYNAMIC_DRAW;
        case EAccessSpecifier::DYNAMIC_READ:
            return GL_DYNAMIC_READ;
        case EAccessSpecifier::DYNAMIC_COPY:
            return GL_DYNAMIC_COPY;
        case EAccessSpecifier::STATIC_DRAW:
            return GL_STATIC_DRAW;
        case EAccessSpecifier::STATIC_READ:
            return GL_STATIC_READ;
        case EAccessSpecifier::STATIC_COPY:
            return GL_STATIC_COPY;
        default:
            return GL_INVALID_ENUM;
        }
    }

    ShaderStorageBuffer::ShaderStorageBuffer(const EAccessSpecifier p_accessSpecifier, const uint32_t p_bindIndex)
        : m_bindIndex(p_bindIndex), m_accessSpecifier(p_accessSpecifier)
    {
        glGenBuffers(1, &m_id);
    }

    ShaderStorageBuffer::ShaderStorageBuffer(ShaderStorageBuffer&& p_other) noexcept
        : m_id(p_other.m_id), m_bindIndex(p_other.m_bindIndex), m_accessSpecifier(p_other.m_accessSpecifier)
    {
        p_other.m_id = 0;
    }

    ShaderStorageBuffer::~ShaderStorageBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    ShaderStorageBuffer& ShaderStorageBuffer::operator=(ShaderStorageBuffer&& p_other) noexcept
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

    void ShaderStorageBuffer::SetBindIndex(const uint32_t p_bindIndex)
    {
        m_bindIndex = p_bindIndex;
    }

    void ShaderStorageBuffer::Bind(const uint32_t p_bindIndex)
    {
        SetBindIndex(p_bindIndex);
        Bind();
    }

    void ShaderStorageBuffer::Bind() const
    {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_bindIndex, m_id);
    }

    void ShaderStorageBuffer::Unbind() const
    {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_bindIndex, 0);
    }

    void ShaderStorageBuffer::SetRawData(const void* p_data, const size_t p_size) const
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
        glBufferData(GL_SHADER_STORAGE_BUFFER, static_cast<GLsizeiptr>(p_size), p_data, ToGLEnum(m_accessSpecifier));
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    void ShaderStorageBuffer::SetRawSubData(const void* p_data, const size_t p_size, const intptr_t p_offset) const
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
        glBufferSubData(GL_SHADER_STORAGE_BUFFER, p_offset, static_cast<GLsizeiptr>(p_size), p_data);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }
}
