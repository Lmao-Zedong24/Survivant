#ifndef __LIBMATH__ANGLE__RADIAN_INL__
#define __LIBMATH__ANGLE__RADIAN_INL__

#include "Arithmetic.h"
#include "Degree.h"
#include "Radian.h"
#include "Trigonometry.h"

namespace LibMath
{
    constexpr Radian::Radian() : Radian(0)
    {
    }

    constexpr Radian::Radian(const float angle) : m_value(angle)
    {
    }

    constexpr Radian::Radian(const Radian& other) : Radian(other.m_value)
    {
    }

    constexpr Radian::operator Degree() const
    {
        return Degree(m_value * g_rad2Deg);
    }

    constexpr Radian& Radian::operator=(const Radian& other)
    {
        if (this == &other)
            return *this;

        this->m_value = other.m_value;

        return *this;
    }

    constexpr Radian& Radian::operator+=(const Radian& angle)
    {
        this->m_value += angle.m_value;

        return *this;
    }

    constexpr Radian& Radian::operator-=(const Radian& angle)
    {
        this->m_value -= angle.m_value;

        return *this;
    }

    constexpr Radian& Radian::operator*=(const float val)
    {
        this->m_value *= val;

        return *this;
    }

    constexpr Radian& Radian::operator/=(const float val)
    {
        this->m_value /= val;

        return *this;
    }

    constexpr void Radian::wrap(const bool useNegative)
    {
        if (useNegative)
            this->m_value = LibMath::wrap(this->m_value, -g_pi, g_pi);
        else
            this->m_value = LibMath::wrap(this->m_value, 0.f, 2.f * g_pi);
    }

    constexpr float Radian::degree(const bool useNegative) const
    {
        Degree deg = Degree(*this);
        deg.wrap(useNegative);

        return deg.raw();
    }

    constexpr float Radian::radian(const bool useNegative) const
    {
        Radian tmp = Radian(*this);
        tmp.wrap(useNegative);

        return tmp.raw();
    }

    constexpr float Radian::raw() const
    {
        return this->m_value;
    }

    constexpr bool operator<(const Radian& lhs, const Radian& rhs)
    {
        return lhs.raw() < rhs.raw();
    }

    constexpr bool operator<(const Radian& lhs, const Degree& rhs)
    {
        return lhs.radian() < rhs.radian();
    }

    constexpr bool operator<=(const Radian& lhs, const Radian& rhs)
    {
        return rhs >= lhs;
    }

    constexpr bool operator<=(const Radian& lhs, const Degree& rhs)
    {
        return rhs >= lhs;
    }

    constexpr bool operator>(const Radian& lhs, const Radian& rhs)
    {
        return rhs < lhs;
    }

    constexpr bool operator>(const Radian& lhs, const Degree& rhs)
    {
        return rhs < lhs;
    }

    constexpr bool operator>=(const Radian& lhs, const Radian& rhs)
    {
        return !(lhs < rhs);
    }

    constexpr bool operator>=(const Radian& lhs, const Degree& rhs)
    {
        return !(lhs < rhs);
    }

    constexpr bool operator==(const Radian& lhs, const Radian& rhs)
    {
        return floatEquals(lhs.radian(), rhs.radian());
    }

    constexpr bool operator==(const Radian& rad, const Degree& deg)
    {
        return floatEquals(rad.radian(), deg.radian());
    }

    constexpr Radian operator-(const Radian& angle)
    {
        return Radian(-angle.raw());
    }

    constexpr Radian operator+(Radian lhs, const Radian& rhs)
    {
        return lhs += rhs;
    }

    constexpr Radian operator-(Radian lhs, const Radian& rhs)
    {
        return lhs -= rhs;
    }

    constexpr Radian operator*(Radian radian, const float x)
    {
        return radian *= x;
    }

    constexpr Radian operator/(Radian radian, const float x)
    {
        return radian /= x;
    }

    inline std::ostream& operator<<(std::ostream& stream, const Radian& radian)
    {
        return stream << radian.raw();
    }

    inline std::istream& operator>>(std::istream& stream, Radian& radian)
    {
        float val;
        stream >> val;
        radian = Radian(val);

        return stream;
    }

    constexpr Radian Literal::operator ""_rad(const long double angle)
    {
        return Radian(static_cast<float>(angle));
    }

    constexpr Radian Literal::operator ""_rad(const unsigned long long int angle)
    {
        return Radian(static_cast<float>(angle));
    }
}

#endif // !__LIBMATH__ANGLE__RADIAN_INL__
