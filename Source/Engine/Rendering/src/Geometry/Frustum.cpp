#include "SurvivantRendering/Geometry/Frustum.h"

using namespace LibMath;

namespace SvRendering::Geometry
{
    // Adapted from https://www8.cs.umu.se/kurser/5DV051/HT12/lab/plane_extraction.pdf
    Frustum::Frustum(const Matrix4& p_viewProjection)
    {
        for (int8_t i = 0; i < 4; ++i)
            m_planes[PLANE_LEFT][i] = p_viewProjection(3, i) + p_viewProjection(0, i);

        for (int8_t i = 0; i < 4; ++i)
            m_planes[PLANE_RIGHT][i] = p_viewProjection(3, i) - p_viewProjection(0, i);

        for (int8_t i = 0; i < 4; ++i)
            m_planes[PLANE_TOP][i] = p_viewProjection(3, i) - p_viewProjection(1, i);

        for (int8_t i = 0; i < 4; ++i)
            m_planes[PLANE_BOTTOM][i] = p_viewProjection(3, i) + p_viewProjection(1, i);

        for (int8_t i = 0; i < 4; ++i)
            m_planes[PLANE_NEAR][i] = p_viewProjection(3, i) + p_viewProjection(2, i);

        for (int8_t i = 0; i < 4; ++i)
            m_planes[PLANE_FAR][i] = p_viewProjection(3, i) - p_viewProjection(2, i);

        for (Vector4& plane : m_planes)
        {
            const float length = squareRoot(plane.m_x * plane.m_x + plane.m_y * plane.m_y + plane.m_z * plane.m_z);

            if (length > 0)
                plane /= length;
        }
    }

    bool Frustum::Intersects(const Vector3& p_point) const
    {
        for (const Vector4& plane : m_planes)
        {
            if (plane.dot(Vector4(p_point, 1.f)) < 0.f)
                return false;
        }

        return true;
    }

    bool Frustum::Intersects(const BoundingSphere& p_boundingSphere) const
    {
        for (const Vector4& plane : m_planes)
        {
            if (plane.xyz().dot(p_boundingSphere.m_center) + plane.m_w + p_boundingSphere.m_radius < 0.f)
                return false;
        }

        return true;
    }

    bool Frustum::Intersects(const BoundingBox& p_boundingBox) const
    {
        for (auto plane : m_planes)
        {
            Vector3 planeMin, planeMax;

            planeMin.m_x = plane.m_x > 0 ? p_boundingBox.m_min.m_x : p_boundingBox.m_max.m_x;
            planeMin.m_y = plane.m_y > 0 ? p_boundingBox.m_min.m_y : p_boundingBox.m_max.m_y;
            planeMin.m_z = plane.m_z > 0 ? p_boundingBox.m_min.m_z : p_boundingBox.m_max.m_z;

            planeMax.m_x = plane.m_x > 0 ? p_boundingBox.m_max.m_x : p_boundingBox.m_min.m_x;
            planeMax.m_y = plane.m_y > 0 ? p_boundingBox.m_max.m_y : p_boundingBox.m_min.m_y;
            planeMax.m_z = plane.m_z > 0 ? p_boundingBox.m_max.m_z : p_boundingBox.m_min.m_z;

            if (plane.xyz().dot(planeMin) + plane.m_w < 0.f && plane.xyz().dot(planeMax) + plane.m_w < 0.f)
                return false;
        }

        return true;
    }
}
