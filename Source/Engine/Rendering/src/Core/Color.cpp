#include "SurvivantRendering/Core/Color.h"

using namespace LibMath;

namespace SvRendering::Core
{
    const Color Color::red       = { 1.f, 0.f, 0.f, 1.f };
    const Color Color::green     = { 0.f, 1.f, 0.f, 1.f };
    const Color Color::blue      = { 0.f, 0.f, 1.f, 1.f };
    const Color Color::cyan      = { 0.f, 1.f, 1.f, 1.f };
    const Color Color::magenta   = { 1.f, 0.f, 1.f, 1.f };
    const Color Color::yellow    = { 1.f, 1.f, 0.f, 1.f };
    const Color Color::skyBlue   = { .529f, .808f, .922f, 1.f };
    const Color Color::lime      = { .75f, 1.f, 0.f, 1.f };
    const Color Color::orange    = { .529f, .808f, .922f, 1.f };
    const Color Color::black     = { 0.f, 0.f, 0.f, 1.f };
    const Color Color::darkGray  = { .25f, .25f, .25f, 1.f };
    const Color Color::gray      = { .5f, .5f, .5f, 1.f };
    const Color Color::lightGray = { .75f, .75f, .75f, 1.f };
    const Color Color::white     = { 1.f, 1.f, 1.f, 1.f };
    const Color Color::clear     = { 0.f, 0.f, 0.f, 0.f };

    Color::Color(const float p_r, const float p_g, const float p_b)
        : Color(p_r, p_g, p_b, 1)
    {
    }

    Color::Color(const float p_r, const float p_g, const float p_b, const float p_a)
        : m_r(p_r), m_g(p_g), m_b(p_b), m_a(p_a)
    {
    }

    Color::Color(const Vector3& p_rgb)
        : Color(p_rgb.m_x, p_rgb.m_y, p_rgb.m_z)
    {
    }

    Color::Color(const Vector3& p_rgb, const float p_a)
        : Color(p_rgb.m_x, p_rgb.m_y, p_rgb.m_z, p_a)
    {
    }

    Color::Color(const Vector4& p_rgba)
        : Color(p_rgba.m_x, p_rgba.m_y, p_rgba.m_z, p_rgba.m_w)
    {
    }

    Color::operator Vector3() const
    {
        return { m_r, m_g, m_b };
    }

    Color::operator Vector4() const
    {
        return { m_r, m_g, m_b, m_a };
    }

    Color Color::operator+(const Color& p_other) const
    {
        return Vector4(*this) + Vector4(p_other);
    }

    Color Color::operator-(const Color& p_other) const
    {
        return Vector4(*this) - Vector4(p_other);
    }

    Color Color::operator*(const Color& p_other) const
    {
        return Vector4(*this) * Vector4(p_other);
    }

    Color Color::operator/(const Color& p_other) const
    {
        return Vector4(*this) / Vector4(p_other);
    }

    Color Color::operator*(const float p_scalar) const
    {
        return Vector4(*this) * Vector4(p_scalar);
    }

    Color Color::operator/(const float p_scalar) const
    {
        return *this / Vector4(p_scalar);
    }

    Color& Color::operator*=(const float p_scalar)
    {
        return *this *= Vector4(p_scalar);
    }

    Color& Color::operator/=(const float p_scalar)
    {
        return *this /= Vector4(p_scalar);
    }

    Color& Color::operator+=(const Color& p_other)
    {
        return *this = *this + p_other;
    }

    Color& Color::operator-=(const Color& p_other)
    {
        return *this = *this - p_other;
    }

    Color& Color::operator*=(const Color& p_other)
    {
        return *this = *this * p_other;
    }

    Color& Color::operator/=(const Color& p_other)
    {
        return *this = *this / p_other;
    }
}
