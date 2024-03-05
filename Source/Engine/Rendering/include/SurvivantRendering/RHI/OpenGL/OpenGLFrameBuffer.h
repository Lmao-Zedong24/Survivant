#pragma once
#include "SurvivantRendering/RHI/IFrameBuffer.h"

namespace SvRendering::RHI
{
    class OpenGLFrameBuffer final : public IFrameBuffer
    {
    public:
        /**
         * \brief Creates a default frame buffer
         */
        OpenGLFrameBuffer();

        /**
         * \brief Disable frame buffer copying
         */
        OpenGLFrameBuffer(const OpenGLFrameBuffer&) = delete;

        /**
         * \brief Creates a move copy of the given frame buffer
         * \param p_other The moved frame buffer
         */
        OpenGLFrameBuffer(OpenGLFrameBuffer&& p_other) noexcept;

        /**
         * \brief Destroys the given frame buffer
         */
        ~OpenGLFrameBuffer() override;

        /**
         * \brief Disable frame buffer copying
         */
        OpenGLFrameBuffer& operator=(const OpenGLFrameBuffer&) = delete;

        /**
         * \brief Moves the given frame buffer into this one
         * \param p_other The moved frame buffer
         * \return A reference to the modified frame buffer
         */
        OpenGLFrameBuffer& operator=(OpenGLFrameBuffer&& p_other) noexcept;

        /**
         * \brief Binds the frame buffer
         */
        void bind() override;

        /**
         * \brief Unbinds the frame buffer
         */
        void unbind() override;

        /**
         * \brief Attaches the given texture to the frame buffer
         * \param p_texture The texture to attach
         * \param p_attachment The target attachment
         */
        void attach(const ITexture& p_texture, Enums::EFrameBufferAttachment p_attachment) override;

        /**
         * \brief Detaches the given attachment from the frame buffer
         * \param p_attachment The attachment to detach
         */
        void detach(Enums::EFrameBufferAttachment p_attachment) override;

    private:
        uint32_t m_id;
    };
}
