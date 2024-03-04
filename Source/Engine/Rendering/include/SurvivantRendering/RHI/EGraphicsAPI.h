#pragma once
#include <cstdint>

namespace SvRendering::RHI
{
    /**
     * \brief Supported rendering apis
     */
    enum class EGraphicsAPI : uint8_t
    {
        NONE,
        OPENGL
    };
}
