#include "SurvivantRendering/Core/Buffers/ShaderStorageBuffer.h"

#include <glad/gl.h>

using namespace SvRendering::Enums;

namespace SvRendering::Core::Buffers
{
    GLenum ToGLEnum(EAccessSpecifier p_accessSpecifier)
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

    ShaderStorageBuffer::ShaderStorageBuffer(EAccessSpecifier p_accessSpecifier)
    {
        glGenBuffers(1, &m_bufferIndex);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_bufferIndex);
        glBufferData(GL_SHADER_STORAGE_BUFFER, 0, nullptr, ToGLEnum(p_accessSpecifier));
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_bufferIndex);
    }

    void ShaderStorageBuffer::SetBindingPoint(const uint32_t p_bindingPoint)
    {
        m_bindingPoint = p_bindingPoint;
    }

    void ShaderStorageBuffer::Bind(const uint32_t p_bindingPoint)
    {
        SetBindingPoint(p_bindingPoint);
        Bind();
    }

    void ShaderStorageBuffer::Bind() const
    {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_bindingPoint, m_bufferIndex);
    }

    void ShaderStorageBuffer::Unbind()
    {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_bindingPoint, 0);
        m_bindingPoint = 0;
    }

    void ShaderStorageBuffer::SendBlocks(const void* p_data, const size_t p_blockSize) const
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_bufferIndex);
        glBufferData(GL_SHADER_STORAGE_BUFFER, static_cast<GLsizeiptr>(p_blockSize), p_data, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }
}
