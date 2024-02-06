#pragma once
#include <cstdint>

namespace SvRendering::Core::Buffers
{
    class Buffer
    {
    public:
        Buffer(const Buffer& p_other) = delete;
        Buffer(Buffer&& p_other) noexcept;
        virtual ~Buffer();

        Buffer& operator=(const Buffer& p_other) = delete;
        Buffer& operator=(Buffer&& p_other) noexcept;

        /**
         * \brief Binds the buffer to the current context
         */
        virtual void Bind() const = 0;

    protected:
        Buffer() = default;

        uint32_t m_bufferIndex = 0;
    };
}
