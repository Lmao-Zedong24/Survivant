#include "SurvivantRendering/RHI/OpenGL/OpenGLUniformBuffer.h"

#include "SurvivantRendering/Enums/EAccessMode.h"
#include "SurvivantRendering/RHI/OpenGL/OpenGLAPI.h"

#include <SurvivantCore/Debug/Assertion.h>

#include <algorithm>

#include <glad/gl.h>

using namespace SvRendering::Enums;

namespace SvRendering::RHI
{
    OpenGLUniformBuffer::OpenGLUniformBuffer(const EAccessMode p_accessMode, const uint32_t p_bindIndex)
        : IUniformBuffer(p_accessMode, p_bindIndex)
    {
        glGenBuffers(1, &m_id);
    }

    OpenGLUniformBuffer::OpenGLUniformBuffer(OpenGLUniformBuffer&& p_other) noexcept
        : IUniformBuffer(std::forward<IUniformBuffer&&>(p_other)), m_id(p_other.m_id)
    {
        p_other.m_id = 0;
    }

    OpenGLUniformBuffer::~OpenGLUniformBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    OpenGLUniformBuffer& OpenGLUniformBuffer::operator=(OpenGLUniformBuffer&& p_other) noexcept
    {
        if (&p_other == this)
            return *this;

        glDeleteBuffers(1, &m_id);

        m_id       = p_other.m_id;
        p_other.m_id = 0;

        IUniformBuffer::operator=(std::move(p_other));

        return *this;
    }

    void OpenGLUniformBuffer::Bind()
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, m_bindIndex, m_id);
    }

    void OpenGLUniformBuffer::Unbind()
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, m_bindIndex, 0);
    }

    void OpenGLUniformBuffer::SetRawData(const void* p_data, const size_t p_size)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, m_id);
        glBufferData(GL_UNIFORM_BUFFER, static_cast<GLsizeiptr>(p_size), p_data, OpenGLAPI::ToGLEnum(m_accessMode));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void OpenGLUniformBuffer::SetRawSubData(const void* p_data, const size_t p_size, const intptr_t p_offset)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, m_id);
        glBufferSubData(GL_UNIFORM_BUFFER, p_offset, static_cast<GLsizeiptr>(p_size), p_data);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
}
