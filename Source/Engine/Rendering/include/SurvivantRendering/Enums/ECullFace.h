#pragma once
#include <cstdint>

namespace SvRendering::Enums
{
    /**
     * \brief Supported cull-face options
     */
    enum class ECullFace : uint8_t
    {
        FRONT,
        BACK,
        FRONT_AND_BACK
    };
}
