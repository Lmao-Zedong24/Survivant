#pragma once
#include <Vector/Vector2.h>
#include <Vector/Vector3.h>

namespace SvRendering::Geometry
{
    struct Vertex
    {
        LibMath::Vector3 m_position;
        LibMath::Vector3 m_normal;
        LibMath::Vector2 m_textureUV;
        LibMath::Vector3 m_tangent;
        LibMath::Vector3 m_bitangent;
    };
}
