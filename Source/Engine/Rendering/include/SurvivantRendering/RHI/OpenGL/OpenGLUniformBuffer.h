#pragma once
#include "SurvivantRendering/RHI/IUniformBuffer.h"

namespace SvRendering::RHI
{
    class OpenGLUniformBuffer final : public IUniformBuffer
    {
    public:
        /**
         * \brief Creates a uniform buffer with the given access mode and bind index
         * \param p_accessMode The ubo's access specifier
         * \param p_bindIndex The ubo's binding point
         */
        explicit OpenGLUniformBuffer(Enums::EAccessMode p_accessMode, uint32_t p_bindIndex);

        /**
         * \brief Disable uniform buffer copying
         */
        OpenGLUniformBuffer(const OpenGLUniformBuffer&) = delete;

        /**
         * \brief Creates a move copy of the given uniform buffer
         * \param p_other The ubo to move
         */
        OpenGLUniformBuffer(OpenGLUniformBuffer&& p_other) noexcept;

        /**
         * \brief Destroys the uniform buffer
         */
        ~OpenGLUniformBuffer() override;

        /**
         * \brief Disable uniform buffer copying
         */
        OpenGLUniformBuffer& operator=(const OpenGLUniformBuffer&) = delete;

        /**
         * \brief Moves the given uniform buffer into this one
         * \param p_other The ubo to copy
         * \return A reference to the modified ubo
         */
        OpenGLUniformBuffer& operator=(OpenGLUniformBuffer&& p_other) noexcept;

        /**
         * \brief Binds the ubo to the current binding point
         */
        void Bind() override;

        /**
         * \brief Unbinds the ubo from the current binding point
         */
        void Unbind() override;

        /**
         * \brief Sends the given data block to the buffer
         * \param p_data The data block to send
         * \param p_size The data block's size in bytes
         */
        void SetRawData(const void* p_data, size_t p_size) override;

        /**
         * \brief Sets the buffer's data starting at the given offset
         * \param p_data The data block to send
         * \param p_size The data block's size in bytes
         * \param p_offset The updated data block's offset
         */
        void SetRawSubData(const void* p_data, size_t p_size, ptrdiff_t p_offset) override;

    private:
        uint32_t m_id;
    };
}
