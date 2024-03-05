#include "SurvivantRendering/RHI/OpenGL/OpenGLShaderStorageBuffer.h"

#include "SurvivantRendering/Enums/EAccessMode.h"
#include "SurvivantRendering/RHI/OpenGL/OpenGLAPI.h"

#include <SurvivantCore/Debug/Assertion.h>

#include <algorithm>

#include <glad/gl.h>

using namespace SvRendering::Enums;

namespace SvRendering::RHI
{
    OpenGLShaderStorageBuffer::OpenGLShaderStorageBuffer(const EAccessMode p_accessMode, const uint32_t p_bindIndex)
        : IShaderStorageBuffer(p_accessMode, p_bindIndex)
    {
        glGenBuffers(1, &m_id);
    }

    OpenGLShaderStorageBuffer::OpenGLShaderStorageBuffer(OpenGLShaderStorageBuffer&& p_other) noexcept
        : IShaderStorageBuffer(std::forward<IShaderStorageBuffer&&>(p_other)), m_id(p_other.m_id)
    {
        p_other.m_id = 0;
    }

    OpenGLShaderStorageBuffer::~OpenGLShaderStorageBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    OpenGLShaderStorageBuffer& OpenGLShaderStorageBuffer::operator=(OpenGLShaderStorageBuffer&& p_other) noexcept
    {
        if (&p_other == this)
            return *this;

        glDeleteBuffers(1, &m_id);

        m_id         = p_other.m_id;
        p_other.m_id = 0;

        IShaderStorageBuffer::operator=(std::move(p_other));

        return *this;
    }

    void OpenGLShaderStorageBuffer::Bind()
    {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_bindIndex, m_id);
    }

    void OpenGLShaderStorageBuffer::Unbind()
    {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_bindIndex, 0);
    }

    void OpenGLShaderStorageBuffer::SetRawData(const void* p_data, const size_t p_size)
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
        glBufferData(GL_SHADER_STORAGE_BUFFER, static_cast<GLsizeiptr>(p_size), p_data, OpenGLAPI::ToGLEnum(m_accessMode));
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    void OpenGLShaderStorageBuffer::SetRawSubData(const void* p_data, const size_t p_size, const intptr_t p_offset)
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
        glBufferSubData(GL_SHADER_STORAGE_BUFFER, p_offset, static_cast<GLsizeiptr>(p_size), p_data);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }
}
