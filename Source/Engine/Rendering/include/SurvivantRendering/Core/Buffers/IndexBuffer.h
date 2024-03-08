#pragma once
#include <vector>

#include "SurvivantRendering/Core/Buffers/Buffer.h"

namespace SvRendering::Core::Buffers
{
    class IndexBuffer final : public Buffer
    {
    public:
        IndexBuffer(const uint32_t* p_indices, intptr_t p_indexCount);
        explicit IndexBuffer(const std::vector<uint32_t>& p_indices);

        /**
         * \brief Binds the index buffer object to the current context
         */
        void Bind() const override;

        /**
         * \brief Unbinds the index buffer from the current context
         */
        static void Unbind();
    };
}
