#pragma once
#include "SurvivantRendering/Core/Buffers/Buffer.h"
#include "SurvivantRendering/Enums/EAccessSpecifier.h"

namespace SvRendering::Core::Buffers
{
    class ShaderStorageBuffer final : public Buffer
    {
    public:
        ShaderStorageBuffer() = default;
        explicit ShaderStorageBuffer(Enums::EAccessSpecifier p_accessSpecifier);

        /**
         * \brief Sets the ssbo's binding point
         */
        void SetBindingPoint(uint32_t p_bindingPoint);

        /**
         * \brief Binds the ssbo at the given binding point
         */
        void Bind(uint32_t p_bindingPoint);

        /**
         * \brief Binds the ssbo to the current binding point
         */
        void Bind() const override;

        /**
         * \brief Unbinds the ssbo from the current binding point
         */
        void Unbind();

        /**
         * \brief Sends the data block to the buffer
         * \param p_data The data block to send
         * \param p_count The number of elements in the block
         */
        template <typename T>
        void SendBlocks(T* p_data, size_t p_count) const;

    private:
        uint32_t m_bindingPoint = 0;

        void SendBlocks(const void* p_data, size_t p_blockSize) const;
    };
}

#include "SurvivantRendering/Core/Buffers/ShaderStorageBuffer.inl"
