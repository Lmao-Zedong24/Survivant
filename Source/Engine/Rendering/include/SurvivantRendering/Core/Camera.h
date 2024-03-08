#pragma once
#include "SurvivantRendering/Core/Color.h"

#include "Matrix/Matrix4.h"

#include "SurvivantRendering/Geometry/Frustum.h"

namespace SvRendering::Core
{
    constexpr uint8_t SV_CLEAR_COLOR_OFFSET = 0;
    constexpr uint8_t SV_CLEAR_COLOR_BIT    = 1 << SV_CLEAR_COLOR_OFFSET;

    constexpr uint8_t SV_CLEAR_DEPTH_OFFSET = SV_CLEAR_COLOR_OFFSET + 1;
    constexpr uint8_t SV_CLEAR_DEPTH_BIT    = 1 << SV_CLEAR_DEPTH_OFFSET;

    constexpr uint8_t SV_CLEAR_STENCIL_OFFSET = SV_CLEAR_DEPTH_OFFSET + 1;
    constexpr uint8_t SV_CLEAR_STENCIL_BIT    = 1 << SV_CLEAR_STENCIL_OFFSET;

    constexpr uint8_t SV_CLEAR_MASK = SV_CLEAR_COLOR_BIT | SV_CLEAR_DEPTH_BIT | SV_CLEAR_STENCIL_BIT;

    class Camera
    {
    public:
        using LayerMask = uint32_t;

        /**
         * \brief Creates a camera with the given projection and view matrices
         * \param p_projection The camera's projection matrix
         * \param p_view The camera's view matrix
         */
        explicit Camera(LibMath::Matrix4 p_projection, LibMath::Matrix4 p_view = LibMath::Matrix4(1.f));

        /**
         * \brief Sets the camera's view matrix
         * \param p_view The camera's new view matrix
         */
        void SetView(LibMath::Matrix4 p_view);

        /**
         * \brief Sets the camera's projection matrix
         * \param p_projection The camera's new projection matrix
         */
        void SetProjection(LibMath::Matrix4 p_projection);

        /**
         * \brief Gets the camera's view-projection matrix
         * \return The camera's view-projection matrix
         */
        LibMath::Matrix4 GetViewProjection() const;

        /**
         * \brief Gets the camera's frustum
         * \return The camera's frustum
         */
        Geometry::Frustum GetFrustum() const;

        void Clear() const;

        void  SetClearColor(Color p_color);
        Color GetClearColor() const;

        /**
         * \brief Sets the camera's buffer clearing mask
         * \param p_clearMask The buffer clear mask (any of SV_CLEAR_COLOR_BIT, SV_CLEAR_DEPTH_BIT and SV_CLEAR_STENCIL_BIT)
         */
        void SetClearMask(uint8_t p_clearMask);

        /**
         * \brief Updates the camera's clear mask from the given values
         * \param p_clearColor Whether the color buffer should be cleared
         * \param p_clearDepth Whether the depth buffer should be cleared
         * \param p_clearStencil Whether the stencil buffer should be cleared
         */
        void SetClearMask(bool p_clearColor, bool p_clearDepth, bool p_clearStencil);

        /**
         * \brief Gets the camera's buffer clearing mask
         * \return The camera's clear mask
         */
        uint8_t GetClearMask() const;

        /**
         * \brief Breaks the buffer clearing mask into separate values
         * \param p_clearColor The output target for whether the color buffer should be cleared
         * \param p_clearDepth The output target for whether the depth buffer should be cleared
         * \param p_clearStencil The output target for whether the stencil buffer should be cleared
         */
        void GetClearMask(bool& p_clearColor, bool& p_clearDepth, bool& p_clearStencil) const;

        /**
         * \brief Sets the mask for the layers visible by the camera
         * \param p_cullingMask The camera's culling mask
         */
        void SetCullingMask(LayerMask p_cullingMask);

        /**
         * \brief Gets the camera's culling mask
         * \return The camera's culling layer mask
         */
        LayerMask GetCullingMask() const;

        /**
         * \brief Checks whether the given layer mask is visible by the camera
         * \param p_layerMask The layer mask to check against
         * \return True if the given layer mask is visible by the camera. False otherwise
         */
        bool IsVisible(LayerMask p_layerMask) const;

    private:
        LibMath::Matrix4  m_projectionMatrix;
        LibMath::Matrix4  m_viewMatrix;
        LibMath::Matrix4  m_viewProjection;
        Geometry::Frustum m_frustum;

        Color     m_clearColor  = Color::black;
        uint8_t   m_clearMask   = SV_CLEAR_MASK;
        LayerMask m_cullingMask = static_cast<LayerMask>(-1);

        void OnChange();
    };
}
