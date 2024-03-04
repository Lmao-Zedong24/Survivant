#pragma once
#include <cstdint>

namespace SvRendering::Enums
{
    /**
     * \brief Supported primitive draw modes
     */
    enum class EPrimitiveType : uint8_t
    {
        POINTS,
        LINES,
        LINE_LOOP,
        LINE_STRIP,
        TRIANGLES,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
        LINES_ADJACENCY,
        LINE_STRIP_ADJACENCY,
        TRIANGLES_ADJACENCY,
        TRIANGLE_STRIP_ADJACENCY,
        PATCHES
    };
}
