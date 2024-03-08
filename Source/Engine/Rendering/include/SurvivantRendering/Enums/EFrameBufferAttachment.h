#pragma once
#include <cstdint>

namespace SvRendering::Enums
{
    enum class EFrameBufferAttachment : uint8_t
    {
        DEPTH,
        STENCIL,
        DEPTH_STENCIL,
        COLOR
    };
}
