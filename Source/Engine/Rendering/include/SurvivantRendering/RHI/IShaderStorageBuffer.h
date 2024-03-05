#pragma once
#include "SurvivantRendering/Enums/EAccessMode.h"

#include <cstdint>
#include <memory>

namespace SvRendering::RHI
{
    class IShaderStorageBuffer
    {
    public:
        /**
         * \brief Disable shader storage buffer copying
         */
        IShaderStorageBuffer(const IShaderStorageBuffer&) = delete;

        /**
         * \brief Creates a move copy of the given shader storage buffer
         * \param p_other The ssbo to move
         */
        IShaderStorageBuffer(IShaderStorageBuffer&& p_other) noexcept;

        /**
         * \brief Destroys the given shader storage buffer
         */
        virtual ~IShaderStorageBuffer() = default;

        /**
         * \brief Disable shader storage buffer copying
         */
        IShaderStorageBuffer& operator=(const IShaderStorageBuffer&) = delete;

        /**
         * \brief Moves the given shader storage buffer into this one
         * \param p_other The ssbo to move
         * \return A reference to the modified ssbo
         */
        IShaderStorageBuffer& operator=(IShaderStorageBuffer&& p_other) noexcept;

        /**
         * \brief Binds the ssbo to the current binding point
         */
        virtual void Bind() = 0;

        /**
         * \brief Unbinds the ssbo from the current binding point
         */
        virtual void Unbind() = 0;

        /**
         * \brief Sends the given data block to the buffer
         * \param p_data The data block to send
         * \param p_size The data block's size in bytes
         */
        virtual void SetRawData(const void* p_data, size_t p_size) = 0;

        /**
         * \brief Sets the buffer's data starting at the given offset
         * \param data The data block to send
         * \param size The data block's size in bytes
         * \param offset The updated data block's offset
         */
        virtual void SetRawSubData(const void* data, size_t size, ptrdiff_t offset) = 0;

        /**
         * \brief Sets the ssbo's binding point
         */
        void SetBindIndex(uint32_t p_bindIndex);

        /**
         * \brief Binds the ssbo at the given binding point
         */
        void Bind(uint32_t p_index);

        /**
         * \brief Sends the data block to the buffer
         * \param p_data The data block to send
         * \param p_count The number of elements in the block
         */
        template <typename T>
        void SetData(T* p_data, size_t p_count);

        /**
         * \brief Sets the buffer's data starting at the given offset
         * \param p_data The objects array to send
         * \param p_count The number of elements in the array
         * \param p_offset The updated data block's offset
         */
        template <typename T>
        void SetSubData(const T* p_data, size_t p_count, ptrdiff_t p_offset);

        /**
         * \brief Creates a shader storage buffer for the current render API with the given access specifier
         * \param p_accessMode The buffer's access specifier
         * \param p_bindIndex The buffer's binding point
         * \return The created shader storage buffer
         */
        static std::unique_ptr<IShaderStorageBuffer> Create(Enums::EAccessMode p_accessMode, uint32_t p_bindIndex);

    protected:
        uint32_t           m_bindIndex;
        Enums::EAccessMode m_accessMode;

        /**
         * \brief Creates a shader storage buffer with the given access mode and bind index
         * \param p_accessMode The ssbo's access specifier
         * \param p_bindIndex The ssbo's binding point
         */
        IShaderStorageBuffer(Enums::EAccessMode p_accessMode, uint32_t p_bindIndex);
    };
}

#include "SurvivantRendering/RHI/IShaderStorageBuffer.inl"
