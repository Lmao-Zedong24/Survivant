#pragma once
#include "Vector/Vector3.h"

namespace SvRendering::Geometry
{
    struct BoundingBox
    {
        LibMath::Vector3 m_min;
        LibMath::Vector3 m_max;
    };
}
