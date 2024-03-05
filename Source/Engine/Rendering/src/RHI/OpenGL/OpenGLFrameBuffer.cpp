#include "SurvivantRendering/RHI/OpenGL/OpenGLFrameBuffer.h"

#include "SurvivantRendering/RHI/OpenGL/OpenGLTexture.h"

#include <glad/gl.h>

using namespace SvRendering::Enums;

namespace SvRendering::RHI
{
    GLenum ToGLEnum(const EFrameBufferAttachment p_attachment)
    {
        if (p_attachment > EFrameBufferAttachment::COLOR)
        {
            const uint8_t colorIndex = static_cast<uint8_t>(p_attachment) - static_cast<uint8_t>(EFrameBufferAttachment::COLOR);
            return colorIndex <= GL_COLOR_ATTACHMENT31 - GL_COLOR_ATTACHMENT0 ? GL_COLOR_ATTACHMENT0 + colorIndex : GL_INVALID_ENUM;
        }

        switch (p_attachment)
        {
        case EFrameBufferAttachment::DEPTH:
            return GL_DEPTH_ATTACHMENT;
        case EFrameBufferAttachment::STENCIL:
            return GL_STENCIL_ATTACHMENT;
        case EFrameBufferAttachment::DEPTH_STENCIL:
            return GL_DEPTH_STENCIL_ATTACHMENT;
        case EFrameBufferAttachment::COLOR:
            return GL_COLOR_ATTACHMENT0;
        }

        return GL_INVALID_ENUM;
    }

    OpenGLFrameBuffer::OpenGLFrameBuffer()
    {
        glGenFramebuffers(1, &m_id);
    }

    OpenGLFrameBuffer::OpenGLFrameBuffer(OpenGLFrameBuffer&& p_other) noexcept
        : m_id(p_other.m_id)
    {
        p_other.m_id = 0;
    }

    OpenGLFrameBuffer::~OpenGLFrameBuffer()
    {
        glDeleteFramebuffers(1, &m_id);
    }

    OpenGLFrameBuffer& OpenGLFrameBuffer::operator=(OpenGLFrameBuffer&& p_other) noexcept
    {
        if (this == &p_other)
            return *this;

        glDeleteFramebuffers(1, &m_id);

        m_id         = p_other.m_id;
        p_other.m_id = 0;

        return *this;
    }

    void OpenGLFrameBuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    }

    void OpenGLFrameBuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFrameBuffer::attach(const ITexture& p_texture, const EFrameBufferAttachment p_attachment)
    {
        const OpenGLTexture& openGLTexture = dynamic_cast<const OpenGLTexture&>(p_texture);

        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
        glFramebufferTexture2D(GL_FRAMEBUFFER, ToGLEnum(p_attachment), GL_TEXTURE_2D, openGLTexture.GetId(), 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFrameBuffer::detach(const EFrameBufferAttachment p_attachment)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
        glFramebufferTexture2D(GL_FRAMEBUFFER, ToGLEnum(p_attachment), GL_TEXTURE_2D, 0, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
