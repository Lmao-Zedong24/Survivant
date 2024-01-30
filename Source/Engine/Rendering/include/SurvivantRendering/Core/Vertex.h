#pragma once
#include <Vector/Vector2.h>
#include <Vector/Vector3.h>

namespace SvRendering::Core
{
    struct Vertex
    {
        LibMath::Vector3 m_position;
        LibMath::Vector3 m_normal;
        LibMath::Vector2 m_textureUV;

        bool operator==(const Vertex& p_other) const
        {
            return p_other.m_position == m_position
                && p_other.m_textureUV == m_textureUV
                && p_other.m_normal == m_normal;
        }
    };
}
