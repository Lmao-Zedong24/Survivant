#pragma once
#include <cstdint>

namespace SvRendering::Enums
{
    /**
     * \breif Supported pixel data formats
     */
    enum class EPixelDataFormat : uint8_t
    {
        STENCIL_INDEX,
        DEPTH_COMPONENT,
        DEPTH_STENCIL,
        RED,
        GREEN,
        BLUE,
        ALPHA,
        RG,
        RGB,
        BGR,
        RGBA,
        BGRA
    };
}
