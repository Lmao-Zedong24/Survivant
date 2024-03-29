#pragma once
#include <vector>

#include "SurvivantRendering/Core/Buffers/Buffer.h"
#include "SurvivantRendering/Geometry/Vertex.h"

namespace SvRendering::Core::Buffers
{
    class VertexBuffer final : public Buffer
    {
    public:
        VertexBuffer(const Geometry::Vertex* p_vertices, intptr_t p_verticesCount);
        explicit VertexBuffer(const std::vector<Geometry::Vertex>& p_vertices);

        /**
         * \brief Binds the vertex buffer to the current context
         */
        void Bind() const override;

        /**
         * \brief Unbinds the vertex buffer from the current context
         */
        static void Unbind();
    };
}
