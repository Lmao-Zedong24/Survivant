#pragma once
#include "SurvivantRendering/Enums/EFrameBufferAttachment.h"

#include <memory>

namespace SvRendering::RHI
{
    class ITexture;

    class IFrameBuffer
    {
    public:
        /**
         * \brief Disable frame buffer copying
         */
        IFrameBuffer(const IFrameBuffer&) = delete;

        /**
         * \brief Creates a move copy of the given frame buffer
         * \param other The moved frame buffer
         */
        IFrameBuffer(IFrameBuffer&& other) noexcept = default;

        /**
         * \brief Destroys the given frame buffer
         */
        virtual ~IFrameBuffer() = default;

        /**
         * \brief Disable frame buffer copying
         */
        IFrameBuffer& operator=(const IFrameBuffer&) = delete;

        /**
         * \brief Moves the given frame buffer into this one
         * \param other The moved frame buffer
         * \return A reference to the modified frame buffer
         */
        IFrameBuffer& operator=(IFrameBuffer&& other) noexcept = default;

        /**
         * \brief Binds the frame buffer
         */
        virtual void bind() = 0;

        /**
         * \brief Unbinds the frame buffer
         */
        virtual void unbind() = 0;

        /**
         * \brief Attaches the given texture to the frame buffer
         * \param texture The texture to attach
         * \param attachment The target attachment
         */
        virtual void attach(const ITexture& texture, Enums::EFrameBufferAttachment attachment) = 0;

        /**
         * \brief Detaches the given attachment from the frame buffer
         * \param attachment The attachment to detach
         */
        virtual void detach(Enums::EFrameBufferAttachment attachment) = 0;

        /**
         * \brief Creates a frame buffer for the current render api
         * \return The created frame buffer
         */
        static std::unique_ptr<IFrameBuffer> Create();

    protected:
        IFrameBuffer() = default;
    };
}
