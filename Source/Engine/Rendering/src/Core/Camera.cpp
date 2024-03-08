#include "SurvivantRendering/Core/Camera.h"

#include <glad/gl.h>

namespace SvRendering::Core
{
    Camera::Camera(LibMath::Matrix4 p_projection, LibMath::Matrix4 p_view)
        : m_projectionMatrix(std::move(p_projection)), m_viewMatrix(std::move(p_view)),
        m_viewProjection(m_projectionMatrix * m_viewMatrix), m_frustum(m_viewProjection)
    {
    }

    void Camera::SetView(LibMath::Matrix4 p_view)
    {
        m_viewMatrix = std::move(p_view);
        OnChange();
    }

    void Camera::SetProjection(LibMath::Matrix4 p_projection)
    {
        m_projectionMatrix = std::move(p_projection);
        OnChange();
    }

    LibMath::Matrix4 Camera::GetViewProjection() const
    {
        return m_viewProjection;
    }

    Geometry::Frustum Camera::GetFrustum() const
    {
        return m_frustum;
    }

    void Camera::Clear() const
    {
        glClearColor(m_clearColor.m_r, m_clearColor.m_g, m_clearColor.m_b, m_clearColor.m_a);

        bool clearColor, clearDepth, clearStencil;
        GetClearMask(clearColor, clearDepth, clearStencil);

        glClear
        (
            (clearColor ? GL_COLOR_BUFFER_BIT : 0) |
            (clearDepth ? GL_DEPTH_BUFFER_BIT : 0) |
            (clearStencil ? GL_STENCIL_BUFFER_BIT : 0)
        );
    }

    void Camera::SetClearColor(const Color p_color)
    {
        m_clearColor = p_color;
    }

    Color Camera::GetClearColor() const
    {
        return m_clearColor;
    }

    void Camera::SetClearMask(const uint8_t p_clearMask)
    {
        m_clearMask = p_clearMask & SV_CLEAR_MASK;
    }

    void Camera::SetClearMask(const bool p_clearColor, const bool p_clearDepth, const bool p_clearStencil)
    {
        m_clearMask = static_cast<uint8_t>(
            p_clearColor << SV_CLEAR_COLOR_OFFSET |
            p_clearDepth << SV_CLEAR_DEPTH_OFFSET |
            p_clearStencil << SV_CLEAR_STENCIL_OFFSET
        );
    }

    uint8_t Camera::GetClearMask() const
    {
        return m_clearMask;
    }

    void Camera::GetClearMask(bool& p_clearColor, bool& p_clearDepth, bool& p_clearStencil) const
    {
        p_clearColor   = m_clearMask & SV_CLEAR_COLOR_BIT;
        p_clearDepth   = m_clearMask & SV_CLEAR_DEPTH_BIT;
        p_clearStencil = m_clearMask & SV_CLEAR_STENCIL_BIT;
    }

    void Camera::SetCullingMask(const LayerMask p_cullingMask)
    {
        m_cullingMask = p_cullingMask;
    }

    Camera::LayerMask Camera::GetCullingMask() const
    {
        return m_cullingMask;
    }

    bool Camera::IsVisible(const LayerMask p_layerMask) const
    {
        return (p_layerMask & m_cullingMask) != 0;
    }

    void Camera::OnChange()
    {
        m_viewProjection = m_projectionMatrix * m_viewMatrix;
        m_frustum        = Geometry::Frustum(m_viewProjection);
    }
}
