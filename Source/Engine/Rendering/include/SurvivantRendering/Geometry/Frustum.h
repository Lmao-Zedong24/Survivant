#pragma once
#include "SurvivantRendering/Geometry/BoundingBox.h"
#include "SurvivantRendering/Geometry/BoundingSphere.h"

#include "Vector/Vector4.h"

namespace SvRendering::Geometry
{
    class Frustum
    {
    public:
        enum EPlane : uint8_t
        {
            PLANE_LEFT = 0,
            PLANE_RIGHT,
            PLANE_TOP,
            PLANE_BOTTOM,
            PLANE_NEAR,
            PLANE_FAR,
            PLANE_COUNT
        };

        /**
         * \brief Computes the frustum from the given view-projection matrix
         * \param p_viewProjection The source view-projection matrix
         */
        explicit Frustum(const LibMath::Matrix4& p_viewProjection);

        /**
         * \brief Creates a copy of the given frustum
         * \param p_other The copied frustum
         */
        Frustum(const Frustum& p_other) = default;

        /**
         * \brief Creates a move copy of the given frustum
         * \param p_other The moved frustum
         */
        Frustum(Frustum&& p_other) noexcept = default;

        /**
         * \brief Destroys the frustum
         */
        ~Frustum() = default;

        /**
         * \brief Assigns a copy of the given frustum to this one
         * \param p_other The copied frustum
         * \return The modified frustum
         */
        Frustum& operator=(const Frustum& p_other) = default;

        /**
         * \brief Moves the given frustum into this one
         * \param p_other The moved frustum
         * \return The modified frustum
         */
        Frustum& operator=(Frustum&& p_other) noexcept = default;

        /**
         * \brief Checks if a given point is in the camera's frustum
         * \param p_point The point to check
         * \return True if the point is in the camera's frustum. False otherwise
         */
        bool Intersects(const LibMath::Vector3& p_point) const;

        /**
         * \brief Checks if a given bounding sphere intersects the camera's frustum
         * \param p_boundingSphere The target bounding sphere
         * \return True if the sphere is in the camera's frustum. False otherwise
         */
        bool Intersects(const BoundingSphere& p_boundingSphere) const;

        /**
         * \brief Checks if a given bounding box is in the camera's frustum
         * \param p_boundingBox The target bounding box
         * \return True if the bounding box is in the camera's frustum. False otherwise
         */
        bool Intersects(const BoundingBox& p_boundingBox) const;

    private:
        LibMath::Vector4 m_planes[PLANE_COUNT];
    };
}
