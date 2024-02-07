#pragma once
#include "SurvivantRendering/Core/Buffers/ShaderStorageBuffer.h"

namespace SvRendering::Core::Buffers
{
    template <typename T>
    void ShaderStorageBuffer::SendBlocks(T* p_data, const size_t p_count) const
    {
        SendBlocks(static_cast<const void*>(p_data), p_count * sizeof(T));
    }
}
