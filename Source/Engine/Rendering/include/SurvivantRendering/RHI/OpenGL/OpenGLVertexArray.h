#pragma once
#include "SurvivantRendering/RHI/IVertexArray.h"

namespace SvRendering::RHI
{
    class OpenGLVertexArray final : public IVertexArray
    {
    public:
        /**
         * \brief Creates a vertex array with the given vertex and index buffers
         * \param p_vbo The linked vertex buffer
         * \param p_ebo The linked index buffer
         */
        explicit OpenGLVertexArray(const IVertexBuffer& p_vbo, const IIndexBuffer& p_ebo);

        /**
         * \brief Disable vertex array copying
         */
        OpenGLVertexArray(const OpenGLVertexArray&) = delete;

        /**
         * \brief Creates a move copy of the given vertex array
         * \param p_other The vertex array to move
         */
        OpenGLVertexArray(OpenGLVertexArray&& p_other) noexcept;

        /**
         * \brief Destroys the vertex array
         */
        ~OpenGLVertexArray() override;

        /**
         * \brief Disable vertex array copying
         */
        OpenGLVertexArray& operator=(const OpenGLVertexArray&) = delete;

        /**
         * \brief Moves the given vertex array into this one
         * \param p_other The vertex array to move
         * \return A reference to the modified vertex array
         */
        OpenGLVertexArray& operator=(OpenGLVertexArray&& p_other) noexcept;

        /**
         * \brief Binds the vertex attributes object to the current context
         */
        void Bind() const override;

        /**
         * \brief Unbinds the vertex attributes object from the current context
         */
        void Unbind() const override;

    private:
        uint32_t m_id = 0;
    };
}
