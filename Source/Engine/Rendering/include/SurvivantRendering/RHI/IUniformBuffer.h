#pragma once
#include "SurvivantRendering/Enums/EAccessMode.h"

#include <cstdint>
#include <memory>

namespace SvRendering::RHI
{
    class IUniformBuffer
    {
    public:
        /**
         * \brief Disable uniform buffer copying
         */
        IUniformBuffer(const IUniformBuffer&) = delete;

        /**
         * \brief Creates a move copy of the given uniform buffer
         * \param p_other The ubo to move
         */
        IUniformBuffer(IUniformBuffer&& p_other) noexcept;

        /**
         * \brief Destroys the uniform buffer
         */
        virtual ~IUniformBuffer() = default;

        /**
         * \brief Disable uniform buffer copying
         */
        IUniformBuffer& operator=(const IUniformBuffer&) = delete;

        /**
         * \brief Moves the given uniform buffer into this one
         * \param p_other The ubo to copy
         * \return A reference to the modified ubo
         */
        IUniformBuffer& operator=(IUniformBuffer&& p_other) noexcept;

        /**
         * \brief Binds the ubo to the current binding point
         */
        virtual void Bind() = 0;

        /**
         * \brief Unbinds the ubo from the current binding point
         */
        virtual void Unbind() = 0;

        /**
         * \brief Sends the data block to the buffer
         * \param p_data The data block to send
         * \param p_size The data block's size in bytes
         */
        virtual void SetRawData(const void* p_data, size_t p_size) = 0;

        /**
         * \brief Sets the buffer's data starting at the given offset
         * \param p_data The data block to send
         * \param p_size The data block's size in bytes
         * \param p_offset The updated data block's offset
         */
        virtual void SetRawSubData(const void* p_data, size_t p_size, ptrdiff_t p_offset) = 0;

        /**
         * \brief Sets the ubo's binding point
         */
        void SetBindIndex(uint32_t p_bindIndex);

        /**
         * \brief Binds the ubo at the given binding point
         */
        void Bind(uint32_t p_index);

        /**
         * \brief Sends the given objects array to the buffer
         * \param p_data The objects array to send
         * \param p_count The number of elements in the array
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
         * \brief Creates a uniform buffer for the current render API with the given access specifier and bind index
         * \param p_accessMode The buffer's access specifier
         * \param p_bindIndex The buffer's binding point
         * \return The created uniform buffer
         */
        static std::unique_ptr<IUniformBuffer> Create(Enums::EAccessMode p_accessMode, uint32_t p_bindIndex);

    protected:
        uint32_t           m_bindIndex;
        Enums::EAccessMode m_accessMode;

        /**
         * \brief Creates a uniform buffer with the given access mode and bind index
         * \param p_accessMode The ubo's access specifier
         * \param p_bindIndex The ubo's binding point
         */
        IUniformBuffer(Enums::EAccessMode p_accessMode, uint32_t p_bindIndex);
    };
}

#include "SurvivantRendering/RHI/IUniformBuffer.inl"
