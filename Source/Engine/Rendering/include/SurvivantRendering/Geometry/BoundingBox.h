#pragma once
#include "Vector/Vector3.h"

namespace SvRendering::Geometry
{
    struct BoundingBox
    {
        LibMath::Vector3 m_min;
        LibMath::Vector3 m_max;
    };

    inline BoundingBox TransformBoundingBox(BoundingBox boundingBox, const LibMath::Matrix4& transform)
    {
        LibMath::Vector3 corners[8]
        {
            boundingBox.m_min,
            { boundingBox.m_min.m_x, boundingBox.m_max.m_y, boundingBox.m_min.m_z },
            { boundingBox.m_min.m_x, boundingBox.m_min.m_y, boundingBox.m_max.m_z },
            { boundingBox.m_min.m_x, boundingBox.m_max.m_y, boundingBox.m_max.m_z },
            { boundingBox.m_max.m_x, boundingBox.m_min.m_y, boundingBox.m_max.m_z },
            { boundingBox.m_max.m_x, boundingBox.m_max.m_y, boundingBox.m_min.m_z },
            { boundingBox.m_max.m_x, boundingBox.m_min.m_y, boundingBox.m_min.m_z },
            boundingBox.m_max
        };

        boundingBox.m_min = LibMath::Vector3(std::numeric_limits<float>::max());
        boundingBox.m_max = LibMath::Vector3(std::numeric_limits<float>::lowest());

        for (LibMath::Vector3& corner : corners)
        {
            corner            = (transform * LibMath::Vector4(corner, 1.f)).xyz();
            boundingBox.m_min = min(boundingBox.m_min, corner);
            boundingBox.m_max = max(boundingBox.m_max, corner);
        }

        return boundingBox;
    }
}
