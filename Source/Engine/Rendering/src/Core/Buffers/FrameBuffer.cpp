#include "SurvivantRendering/Core/Buffers/FrameBuffer.h"

#include "SurvivantRendering/Enums/EFrameBufferAttachment.h"
#include "SurvivantRendering/RHI/OpenGL/OpenGLTexture.h"

#include <glad/gl.h>

using namespace SvRendering::Enums;
using namespace SvRendering::RHI;

namespace SvRendering::Core::Buffers
{
    GLenum ToGLEnum(const EFrameBufferAttachment p_attachment)
    {
        if (p_attachment > EFrameBufferAttachment::COLOR)
        {
            const uint8_t attachment = static_cast<uint8_t>(p_attachment) - static_cast<uint8_t>(EFrameBufferAttachment::COLOR);
            return attachment <= GL_COLOR_ATTACHMENT31 - GL_COLOR_ATTACHMENT0 ? GL_COLOR_ATTACHMENT0 + attachment : GL_INVALID_ENUM;
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

    FrameBuffer::FrameBuffer()
    {
        glGenFramebuffers(1, &m_id);
    }

    FrameBuffer::FrameBuffer(FrameBuffer&& p_other) noexcept
        : m_id(p_other.m_id)
    {
        p_other.m_id = 0;
    }

    FrameBuffer::~FrameBuffer()
    {
        glDeleteFramebuffers(1, &m_id);
    }

    FrameBuffer& FrameBuffer::operator=(FrameBuffer&& p_other) noexcept
    {
        if (this == &p_other)
            return *this;

        glDeleteFramebuffers(1, &m_id);

        m_id         = p_other.m_id;
        p_other.m_id = 0;

        return *this;
    }

    void FrameBuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    }

    void FrameBuffer::Unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBuffer::Attach(const ITexture& p_texture, const EFrameBufferAttachment p_attachmentMode) const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
        glFramebufferTexture2D(GL_FRAMEBUFFER, ToGLEnum(p_attachmentMode), GL_TEXTURE_2D, dynamic_cast<const OpenGLTexture&>(p_texture).GetId(), 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBuffer::Detach(const EFrameBufferAttachment p_attachmentMode) const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
        glFramebufferTexture2D(GL_FRAMEBUFFER, ToGLEnum(p_attachmentMode), GL_TEXTURE_2D, 0, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
