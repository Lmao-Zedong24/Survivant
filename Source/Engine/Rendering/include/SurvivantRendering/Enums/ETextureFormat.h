#pragma once
#include <cstdint>

namespace SvRendering::Enums
{
    /**
     * \brief Supported texture formats
     */
    enum class ETextureFormat : uint8_t
    {
        RED,
        RG,
        RGB,
        RGBA,
        BGR,
        BGRA,
        STENCIL_INDEX,
        DEPTH_COMPONENT,
        DEPTH_STENCIL
    };
}
