#pragma once
#include <cstdint>

namespace SvRendering::Enums
{
    /**
     * \brief Supported depth/stencil operations comparison algorithms
     */
    enum class ECompareAlgorithm : uint8_t
    {
        NEVER,
        LESS,
        EQUAL,
        LESS_EQUAL,
        GREATER,
        NOT_EQUAL,
        GREATER_EQUAL,
        ALWAYS
    };
}
