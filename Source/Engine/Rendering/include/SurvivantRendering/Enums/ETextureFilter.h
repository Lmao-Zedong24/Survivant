#pragma once
#include <cstdint>

namespace SvRendering::Enums
{
    /**
     * \brief Supported texture filters
     */
    enum class ETextureFilter : uint8_t
    {
        NEAREST,
        LINEAR,
        NEAREST_MIPMAP_NEAREST,
        LINEAR_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR,
        LINEAR_MIPMAP_LINEAR
    };
}
