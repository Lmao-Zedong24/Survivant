#pragma once

namespace SvRendering::Enums
{
    /**
    * \brief OpenGL compare algorithm enum wrapper
    */
    enum class EAccessSpecifier
    {
        STREAM_DRAW,
        STREAM_READ,
        STREAM_COPY,
        DYNAMIC_DRAW,
        DYNAMIC_READ,
        DYNAMIC_COPY,
        STATIC_DRAW,
        STATIC_READ,
        STATIC_COPY
    };
}
