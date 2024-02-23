#pragma once
#include "SurvivantRendering/Enums/EAccessSpecifier.h"

#include <cstdint>

namespace SvRendering::Core::Buffers
{
    class UniformBuffer final
    {
    public:
        explicit UniformBuffer(Enums::EAccessSpecifier p_accessSpecifier, uint32_t p_bindIndex = 0);
        UniformBuffer(const UniformBuffer& p_other) = delete;
        UniformBuffer(UniformBuffer&& p_other) noexcept;

        ~UniformBuffer();

        UniformBuffer& operator=(const UniformBuffer& p_other) = delete;
        UniformBuffer& operator=(UniformBuffer&& p_other) noexcept;

        /**
         * \brief Sets the ubo's binding point
         * \param p_bindIndex The ubo's new binding point
         */
        void SetBindIndex(uint32_t p_bindIndex);

        /**
         * \brief Binds the ubo at the given binding point
         * \param p_bindIndex The target binding point
         */
        void Bind(uint32_t p_bindIndex);

        /**
         * \brief Binds the ubo to the current binding point
         */
        void Bind() const;

        /**
         * \brief Unbinds the ubo from the current binding point
         */
        void Unbind() const;

        /**
         * \brief Sends the data block to the buffer
         * \param p_data The data block to send
         * \param p_size The data block's size in bytes
         */
        void SetRawData(const void* p_data, size_t p_size) const;

        /**
         * \brief Sends the given objects array to the buffer
         * \param p_data The objects array to send
         * \param p_count The number of elements in the array
         */
        template <typename T>
        void SetData(const T* p_data, size_t p_count) const;

        /**
         * \brief Sets the buffer's data starting at the given offset
         * \param p_data The data block to send
         * \param p_size The data block's size in bytes
         * \param p_offset The updated data block's offset
         */
        void SetRawSubData(const void* p_data, size_t p_size, ptrdiff_t p_offset) const;

        /**
         * \brief Sets the buffer's data starting at the given offset
         * \param p_data The objects array to send
         * \param p_count The number of elements in the array
         * \param p_offset The updated data block's offset
         */
        template <typename T>
        void SetSubData(const T* p_data, size_t p_count, ptrdiff_t p_offset) const;

    private:
        uint32_t                m_id;
        uint32_t                m_bindIndex;
        Enums::EAccessSpecifier m_accessSpecifier;
    };
}

#include "SurvivantRendering/Core/Buffers/UniformBuffer.inl"
