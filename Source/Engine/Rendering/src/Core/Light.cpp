#include "SurvivantRendering/Core/Light.h"

#include "SurvivantRendering/Enums/ELightType.h"

using namespace LibMath;

using namespace SvRendering::Enums;

namespace SvRendering::Core
{
    Light::Light(const Color& color)
        : m_color(color)
    {
    }

    Matrix4 Light::getMatrix() const
    {
        Matrix4 lightMat;

        lightMat(0, 0) = m_color.m_r;
        lightMat(0, 1) = m_color.m_g;
        lightMat(0, 2) = m_color.m_b;
        lightMat(0, 3) = m_color.m_a;

        lightMat(3, 3) = static_cast<float>(ELightType::AMBIENT);

        return lightMat;
    }

    DirectionalLight::DirectionalLight(const Light& light, const Vector3& direction)
        : Light(light), m_direction(direction)
    {
    }

    Matrix4 DirectionalLight::getMatrix() const
    {
        Matrix4 lightMat(Light::getMatrix());

        lightMat(1, 0) = m_direction.m_x;
        lightMat(2, 0) = m_direction.m_y;
        lightMat(3, 0) = m_direction.m_z;

        lightMat(3, 3) = static_cast<float>(ELightType::DIRECTIONAL);

        return lightMat;
    }

    Attenuation::Attenuation(const float range)
        : Attenuation(1.f, 4.5f / range, 75.f / (range * range))
    {
    }

    Attenuation::Attenuation(const float constant, const float linear, const float quadratic)
        : m_constant(constant), m_linear(linear), m_quadratic(quadratic)
    {
    }

    PointLight::PointLight(const Light&           light, const Vector3& position,
                           const Attenuation& attenuationData)
        : Light(light), m_position(position), m_attenuationData(attenuationData)
    {
    }

    Matrix4 PointLight::getMatrix() const
    {
        Matrix4 lightMat(Light::getMatrix());

        lightMat(1, 1) = m_position.m_x;
        lightMat(2, 1) = m_position.m_y;
        lightMat(3, 1) = m_position.m_z;

        lightMat(1, 2) = m_attenuationData.m_constant;
        lightMat(2, 2) = m_attenuationData.m_linear;
        lightMat(3, 2) = m_attenuationData.m_quadratic;

        lightMat(3, 3) = static_cast<float>(ELightType::POINT);

        return lightMat;
    }

    SpotLight::SpotLight(const Light&           light, const Vector3&          position, const Vector3& direction,
                         const Attenuation& attenuation, const Cutoff& cutoff)
        : Light(light), m_position(position), m_direction(direction),
        m_attenuationData(attenuation), m_cutoff(cutoff)
    {
    }

    Matrix4 SpotLight::getMatrix() const
    {
        Matrix4 lightMat(Light::getMatrix());

        lightMat(1, 0) = m_direction.m_x;
        lightMat(2, 0) = m_direction.m_y;
        lightMat(3, 0) = m_direction.m_z;

        lightMat(1, 1) = m_position.m_x;
        lightMat(2, 1) = m_position.m_y;
        lightMat(3, 1) = m_position.m_z;

        lightMat(1, 2) = m_attenuationData.m_constant;
        lightMat(2, 2) = m_attenuationData.m_linear;
        lightMat(3, 2) = m_attenuationData.m_quadratic;

        lightMat(1, 3) = m_cutoff.m_inner;
        lightMat(2, 3) = m_cutoff.m_outer;

        lightMat(3, 3) = static_cast<float>(ELightType::SPOT);

        return lightMat;
    }
}
