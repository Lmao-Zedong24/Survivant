#pragma once
#include "SurvivantRendering/RHI/IShaderStorageBuffer.h"

namespace SvRendering::RHI
{
    class OpenGLShaderStorageBuffer final : public IShaderStorageBuffer
    {
    public:
        /**
         * \brief Creates a shader storage buffer with the given access mode and bind index
         * \param p_accessMode The ssbo's access specifier
         * \param p_bindIndex The ssbo's binding point
         */
        explicit OpenGLShaderStorageBuffer(Enums::EAccessMode p_accessMode, uint32_t p_bindIndex);

        /**
         * \brief Disable shader storage buffer copying
         */
        OpenGLShaderStorageBuffer(const OpenGLShaderStorageBuffer&) = delete;

        /**
         * \brief Creates a move copy of the given shader storage buffer
         * \param p_other The moved ssbo
         */
        OpenGLShaderStorageBuffer(OpenGLShaderStorageBuffer&& p_other) noexcept;

        /**
         * \brief Destroys the given shader storage buffer
         */
        ~OpenGLShaderStorageBuffer() override;

        /**
         * \brief Disable shader storage buffer copying
         */
        OpenGLShaderStorageBuffer& operator=(const OpenGLShaderStorageBuffer&) = delete;

        /**
         * \brief Moves the given shader storage buffer into this one
         * \param p_other The moved ssbo
         * \return A reference to the modified ssbo
         */
        OpenGLShaderStorageBuffer& operator=(OpenGLShaderStorageBuffer&& p_other) noexcept;

        /**
         * \brief Binds the ssbo to the current binding point
         */
        void Bind() override;

        /**
         * \brief Unbinds the ssbo from the current binding point
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
