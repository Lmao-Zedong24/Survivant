#pragma once
#include "SurvivantRendering/RHI/IIndexBuffer.h"
#include "SurvivantRendering/RHI/IVertexBuffer.h"

namespace SvRendering::RHI
{
    class IVertexArray
    {
    public:
        /**
         * \brief Disable vertex array copying
         */
        IVertexArray(const IVertexArray&) = delete;

        /**
         * \brief Creates a move copy of the given vertex array
         * \param p_other The vertex array to move
         */
        IVertexArray(IVertexArray&& p_other) noexcept = default;

        /**
         * \brief Destroys the vertex array
         */
        virtual ~IVertexArray() = default;

        /**
         * \brief Disable vertex array copying
         */
        IVertexArray& operator=(const IVertexArray&) = delete;

        /**
         * \brief Moves the given vertex array into this one
         * \param p_other The vertex array to move
         * \return A reference to the modified vertex array
         */
        IVertexArray& operator=(IVertexArray&& p_other) noexcept = default;

        /**
         * \brief Binds the vertex attributes object to the current context
         */
        virtual void Bind() const = 0;

        /**
         * \brief Unbinds the vertex attributes object from the current context
         */
        virtual void Unbind() const = 0;

        /**
         * \brief Creates a vertex array for the current render API with the given vertex and index buffers
         * \param p_vbo The vertex array's vertex buffer
         * \param p_ebo The vertex array's index buffer
         * \return The created vertex array
         */
        static std::unique_ptr<IVertexArray> Create(const IVertexBuffer& p_vbo, const IIndexBuffer& p_ebo);

    protected:
        /**
         * \brief Creates a default vertex array
         */
        IVertexArray() = default;
    };
}
