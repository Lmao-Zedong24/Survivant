#pragma once
#include "SurvivantRendering/Core/Buffers/IndexBuffer.h"
#include "SurvivantRendering/Core/Buffers/VertexBuffer.h"

namespace SvRendering::Core
{
    class VertexArray
    {
    public:
        VertexArray() = default;
        explicit VertexArray(const Buffers::VertexBuffer& p_vbo, const Buffers::IndexBuffer& p_ebo);

        VertexArray(const VertexArray& p_other) = delete;
        VertexArray(VertexArray&& p_other) noexcept;
        ~VertexArray();

        VertexArray& operator=(const VertexArray& p_other) = delete;
        VertexArray& operator=(VertexArray&& p_other) noexcept;

        /**
         * \brief Binds the vertex attributes object to the current context
         */
        void Bind() const;

        /**
         * \brief Unbinds the vertex attributes object from the current context
         */
        void Unbind() const;

    private:
        uint32_t m_vao = 0;
    };
}
