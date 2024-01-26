#ifndef __LIBMATH__ANGLE__DEGREE_INL__
#define __LIBMATH__ANGLE__DEGREE_INL__

#include "Arithmetic.h"
#include "Degree.h"
#include "Radian.h"
#include "Trigonometry.h"

namespace LibMath
{
    constexpr Degree::Degree() : m_value(0)
    {
    }

    constexpr Degree::Degree(const float angle) : m_value(angle)
    {
    }

    constexpr Degree::Degree(const Degree& other) : Degree(other.m_value)
    {
    }

    constexpr Degree::operator Radian() const
    {
        return Radian(m_value * g_deg2Rad);
    }

    constexpr Degree& Degree::operator=(const Degree& other)
    {
        if (this == &other)
            return *this;

        this->m_value = other.m_value;

        return *this;
    }

    constexpr Degree& Degree::operator+=(const Degree& angle)
    {
        this->m_value += angle.m_value;

        return *this;
    }

    constexpr Degree& Degree::operator-=(const Degree& angle)
    {
        this->m_value -= angle.m_value;

        return *this;
    }

    constexpr Degree& Degree::operator*=(const float val)
    {
        this->m_value *= val;

        return *this;
    }

    constexpr Degree& Degree::operator/=(const float val)
    {
        this->m_value /= val;

        return *this;
    }

    constexpr void Degree::wrap(const bool useNegative)
    {
        if (useNegative)
            this->m_value = LibMath::wrap(this->m_value, -180.f, 180.f);
        else
            this->m_value = LibMath::wrap(this->m_value, 0.f, 360.f);
    }

    constexpr float Degree::degree(const bool useNegative) const
    {
        Degree tmp = Degree(*this);
        tmp.wrap(useNegative);

        return tmp.raw();
    }

    constexpr float Degree::radian(const bool useNegative) const
    {
        Radian rad = Radian(*this);
        rad.wrap(useNegative);
        return rad.raw();
    }

    constexpr float Degree::raw() const
    {
        return this->m_value;
    }

    constexpr bool operator<(const Degree& lhs, const Degree& rhs)
    {
        return lhs.raw() < rhs.raw();
    }

    constexpr bool operator<(const Degree& lhs, const Radian& rhs)
    {
        return lhs.degree() < rhs.degree();
    }

    constexpr bool operator<=(const Degree& lhs, const Degree& rhs)
    {
        return rhs >= lhs;
    }

    constexpr bool operator<=(const Degree& lhs, const Radian& rhs)
    {
        return rhs >= lhs;
    }

    constexpr bool operator>(const Degree& lhs, const Degree& rhs)
    {
        return rhs < lhs;
    }

    constexpr bool operator>(const Degree& lhs, const Radian& rhs)
    {
        return rhs < lhs;
    }

    constexpr bool operator>=(const Degree& lhs, const Degree& rhs)
    {
        return !(lhs < rhs);
    }

    constexpr bool operator>=(const Degree& lhs, const Radian& rhs)
    {
        return !(lhs < rhs);
    }

    constexpr bool operator==(const Degree& lhs, const Degree& rhs)
    {
        return floatEquals(lhs.degree(), rhs.degree());
    }

    constexpr bool operator==(const Degree& deg, const Radian& rad)
    {
        return rad == deg;
    }

    constexpr Degree operator-(const Degree& angle)
    {
        return Degree(-angle.raw());
    }

    constexpr Degree operator+(Degree lhs, const Degree& rhs)
    {
        return lhs += rhs;
    }

    constexpr Degree operator-(Degree lhs, const Degree& rhs)
    {
        return lhs -= rhs;
    }

    constexpr Degree operator*(Degree degree, const float x)
    {
        return degree *= x;
    }

    constexpr Degree operator/(Degree degree, const float x)
    {
        return degree /= x;
    }

    inline std::ostream& operator<<(std::ostream& stream, const Degree& degrees)
    {
        return stream << degrees.raw();
    }

    inline std::istream& operator>>(std::istream& stream, Degree& degrees)
    {
        float val;
        stream >> val;
        degrees = Degree(val);

        return stream;
    }

    constexpr Degree Literal::operator ""_deg(const long double angle)
    {
        return Degree(static_cast<float>(angle));
    }

    constexpr Degree Literal::operator ""_deg(const unsigned long long int angle)
    {
        return Degree(static_cast<float>(angle));
    }
}

#endif // !__LIBMATH__ANGLE__DEGREE_INL__
