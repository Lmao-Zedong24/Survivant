#pragma once
#include <cstdint>

namespace SvRendering::Enums
{
    /**
     * \brief Supported texture wrap modes
     */
    enum class ETextureWrapMode : uint8_t
    {
        REPEAT,
        MIRRORED_REPEAT,
        CLAMP_TO_EDGE,
        CLAMP_TO_BORDER
    };
}
