#pragma once
#include "SurvivantRendering/RHI/IIndexBuffer.h"

namespace SvRendering::RHI
{
    class OpenGLIndexBuffer final : public IIndexBuffer
    {
    public:
        /**
         * \brief Creates an index buffer with the given indices
         * \param p_indices The array of indices to add to the buffer
         * \param p_count The number of indices in the buffer
         */
        OpenGLIndexBuffer(const uint32_t* p_indices, uint32_t p_count);

        /**
         * \brief Disable index buffer copying
         */
        OpenGLIndexBuffer(const OpenGLIndexBuffer&) = delete;

        /**
         * \brief Creates a move copy of the given index buffer
         * \param p_other The moved index buffer
         */
        OpenGLIndexBuffer(OpenGLIndexBuffer&& p_other) noexcept;

        /**
         * \brief Destroys the given index buffer
         */
        ~OpenGLIndexBuffer() override;

        /**
         * \brief Disable index buffer copying
         */
        OpenGLIndexBuffer& operator=(const OpenGLIndexBuffer&) = delete;

        /**
         * \brief Moves the given index buffer into this one
         * \param p_other The moved index buffer
         * \return A reference to the modified index buffer
         */
        OpenGLIndexBuffer& operator=(OpenGLIndexBuffer&& p_other) noexcept;

        /**
         * \brief Binds the index buffer object to the current context
         */
        void Bind() const override;

        /**
         * \brief Unbinds the index buffer from the current context
         */
        void Unbind() const override;

    private:
        uint32_t m_id = 0;
    };
}
