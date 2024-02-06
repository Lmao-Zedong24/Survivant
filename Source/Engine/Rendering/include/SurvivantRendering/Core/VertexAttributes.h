#pragma once
#include "SurvivantRendering/Core/Buffers/IndexBuffer.h"
#include "SurvivantRendering/Core/Buffers/VertexBuffer.h"

namespace SvRendering::Core
{
    class VertexAttributes
    {
    public:
        VertexAttributes() = default;
        explicit VertexAttributes(const Buffers::VertexBuffer& p_vbo, const Buffers::IndexBuffer& p_ebo);

        VertexAttributes(const VertexAttributes& p_other) = delete;
        VertexAttributes(VertexAttributes&& p_other) noexcept;
        ~VertexAttributes();

        VertexAttributes& operator=(const VertexAttributes& p_other) = delete;
        VertexAttributes& operator=(VertexAttributes&& p_other) noexcept;

        /**
         * \brief Binds the vertex attributes object to the current context
         */
        void Bind() const;

        /**
         * \brief Unbinds the vertex attributes object from the current context
         */
        static void Unbind();

    private:
        uint32_t m_vao = 0;
    };
}
