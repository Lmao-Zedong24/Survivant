#pragma once
#include "SurvivantRendering/Enums/EFrameBufferAttachment.h"
#include "SurvivantRendering/RHI/ITexture.h"

#include <cstdint>

namespace SvRendering::Core::Buffers
{
    class FrameBuffer
    {
    public:
        /**
         * \brief Creates a default framebuffer
         */
        FrameBuffer();

        /**
         * \brief Disable frame buffer copying
         */
        FrameBuffer(const FrameBuffer& p_other) = delete;

        /**
         * \brief Creates a move copy of the given frame buffer
         * \param p_other The moved frame buffer
         */
        FrameBuffer(FrameBuffer&& p_other) noexcept;

        /**
         * \brief Destroys the given frame buffer
         */
        ~FrameBuffer();

        /**
         * \brief Disable frame buffer copying
         */
        FrameBuffer& operator=(const FrameBuffer& p_other) = delete;

        /**
         * \brief Moves the given frame buffer into this one
         * \param p_other The moved frame buffer
         * \return A reference to the modified frame buffer
         */
        FrameBuffer& operator=(FrameBuffer&& p_other) noexcept;

        /**
         * \brief Binds the frame buffer to the current context
         */
        void Bind() const;

        /**
         * \brief Unbinds the current frame buffer
         */
        void Unbind() const;

        /**
         * \brief Attaches the given texture to the frame buffer
         * \param p_texture The texture to attach
         * \param p_attachmentMode The texture's target attachment
         */
        void Attach(const RHI::ITexture& p_texture, Enums::EFrameBufferAttachment p_attachmentMode) const;

        /**
         * \brief Detaches the attachment with the given mode from the frame buffer
         * \param p_attachmentMode The attachment to detach
         */
        void Detach(Enums::EFrameBufferAttachment p_attachmentMode) const;

    private:
        uint32_t m_id;
    };
}
