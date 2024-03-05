#pragma once
#include "SurvivantRendering/RHI/IUniformBuffer.h"

namespace SvRendering::RHI
{
    template <typename T>
    void IUniformBuffer::SetData(T* p_data, const size_t p_count)
    {
        SetRawData(static_cast<const void*>(p_data), p_count * sizeof(T));
    }

    template <typename T>
    void IUniformBuffer::SetSubData(const T* p_data, const size_t p_count, const ptrdiff_t p_offset)
    {
        SetRawSubData(static_cast<const void*>(p_data), p_count * sizeof(T), p_offset);
    }
}
