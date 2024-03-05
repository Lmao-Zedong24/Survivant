#pragma once
#include "SurvivantRendering/RHI/IVertexBuffer.h"

namespace SvRendering::RHI
{
    class OpenGLVertexBuffer final : public IVertexBuffer
    {
    public:
        /**
         * \brief Creates a vertex buffer with the given vertices
         * \param p_vertices The array of vertices to add to the buffer
         * \param p_count The number of vertices in the buffer
         */
        OpenGLVertexBuffer(const Geometry::Vertex* p_vertices, uint32_t p_count);

        /**
         * \brief Disable vertex buffer copying
         */
        OpenGLVertexBuffer(const OpenGLVertexBuffer&) = delete;

        /**
         * \brief Creates a move copy of the given vertex buffer
         * \param p_other The vertex buffer to move
         */
        OpenGLVertexBuffer(OpenGLVertexBuffer&& p_other) noexcept;

        /**
         * \brief Destroys the vertex buffer
         */
        ~OpenGLVertexBuffer() override;

        /**
         * \brief Disable vertex buffer copying
         */
        OpenGLVertexBuffer& operator=(const OpenGLVertexBuffer&) = delete;

        /**
         * \brief Creates a move copy of the given vertex buffer
         * \param p_other The vertex buffer to move
         */
        OpenGLVertexBuffer& operator=(OpenGLVertexBuffer&& p_other) noexcept;

        /**
         * \brief Binds the vertex buffer to the current context
         */
        void Bind() const override;

        /**
         * \brief Unbinds the vertex buffer from the current context
         */
        void Unbind() const override;

    private:
        uint32_t m_id = 0;
    };
}
