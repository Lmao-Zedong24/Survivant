#pragma once
#include "SurvivantRendering/Geometry/Vertex.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace SvRendering::RHI
{
    class IVertexBuffer
    {
    public:
        /**
         * \brief Disable vertex buffer copying
         */
        IVertexBuffer(const IVertexBuffer&) = delete;

        /**
         * \brief Creates a move copy of the given vertex buffer
         * \param p_other The vertex buffer to move
         */
        IVertexBuffer(IVertexBuffer&& p_other) noexcept = default;

        /**
         * \brief Destroys the vertex buffer
         */
        virtual ~IVertexBuffer() = default;

        /**
         * \brief Disable vertex buffer copying
         */
        IVertexBuffer& operator=(const IVertexBuffer&) = delete;

        /**
         * \brief Moves the given vertex buffer into this one
         * \param p_other The vertex buffer to move
         * \return A reference to the modified vertex buffer
         */
        IVertexBuffer& operator=(IVertexBuffer&& p_other) noexcept = default;

        /**
         * \brief Binds the vertex buffer to the current context
         */
        virtual void Bind() const = 0;

        /**
         * \brief Unbinds the vertex buffer from the current context
         */
        virtual void Unbind() const = 0;

        /**
         * \brief Creates a vertex buffer for the current render API with the given vertices
         * \param p_vertices The array of vertices to add to the buffer
         * \param p_count The number of vertices in the buffer
         * \return The created vertex buffer
         */
        static std::unique_ptr<IVertexBuffer> Create(const Geometry::Vertex* p_vertices, uint32_t p_count);

        /**
         * \brief Creates a vertex buffer for the current render API with the given vertices
         * \param p_vertices The array of vertices to add to the buffer
         * \return The created vertex buffer
         */
        static std::unique_ptr<IVertexBuffer> Create(const std::vector<Geometry::Vertex>& p_vertices);

    protected:
        IVertexBuffer() = default;
    };
}
