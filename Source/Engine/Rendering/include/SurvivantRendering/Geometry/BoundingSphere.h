#pragma once
#include "Vector/Vector3.h"

namespace SvRendering::Geometry
{
    struct BoundingSphere
    {
        LibMath::Vector3 m_center;
        float            m_radius;
    };
}
