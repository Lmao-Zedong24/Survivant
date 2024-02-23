#pragma once
#include "SurvivantRendering/Core/Buffers/UniformBuffer.h"

namespace SvRendering::Core::Buffers
{
    template <typename T>
    void UniformBuffer::SetData(const T* p_data, const size_t p_count) const
    {
        SetRawData(static_cast<const void*>(p_data), p_count * sizeof(T));
    }

    template <typename T>
    void UniformBuffer::SetSubData(const T* p_data, const size_t p_count, const ptrdiff_t p_offset) const
    {
        SetRawSubData(static_cast<const void*>(p_data), p_count * sizeof(T), p_offset);
    }
}
