#ifndef __LIBMATH__ANGLE__RADIAN_H__
#define __LIBMATH__ANGLE__RADIAN_H__
#include <iostream>

namespace LibMath
{
    class Degree;

    class Radian
    {
    public:
        constexpr          Radian();
        constexpr explicit Radian(float); // explicit so no ambiguous / implicit conversion from float to angle can happen
        constexpr          Radian(const Radian&);
        ~Radian() = default;

        constexpr operator Degree() const; // Degree angle = Radian{0.5};		// implicit conversion from Radian to Degree

        constexpr Radian& operator=(const Radian&);
        constexpr Radian& operator+=(const Radian&); // Radian angle += Radian{0.5};
        constexpr Radian& operator-=(const Radian&); // Radian angle -= Radian{0.5};
        constexpr Radian& operator*=(float);         // Radian angle *= 3;
        constexpr Radian& operator/=(float);         // Radian angle /= 3;

        constexpr void wrap(bool = false); // true -> limit m_value to range [-pi, pi[	// false -> limit m_value to range [0, 2 pi[

        constexpr float degree(bool = false) const;
        // return angle in degree	// true -> limit value to range [-180, 180[	// false -> limit value to range [0, 360[
        constexpr float radian(bool = true) const;
        // return angle in radian	// true -> limit value to range [-pi, pi[		// false -> limit value to range [0, 2 pi[
        constexpr float raw() const; // return m_angle

    private:
        float m_value;
    };

    constexpr bool operator<(const Radian& lhs, const Radian& rhs); // bool isLess = Radian{.5} < Radian{1.5};	// true
    constexpr bool operator<(const Radian& lhs, const Degree& rhs); // bool isLess = Radian{.5} < Degree{60};	// true

    constexpr bool operator<=(const Radian& lhs, const Radian& rhs); // bool isLessEqual = Radian{.5} <= Radian{.5};	// true
    constexpr bool operator<=(const Radian& lhs, const Degree& rhs); // bool isLessEqual = Radian{.5} <= Degree{60};	// true

    constexpr bool operator>(const Radian& lhs, const Radian& rhs); // bool isGreater = Radian{.5} > Radian{1.5};	// false
    constexpr bool operator>(const Radian& lhs, const Degree& rhs); // bool isGreater = Radian{.5} > Degree{60};	// false

    constexpr bool operator>=(const Radian& lhs, const Radian& rhs); // bool isGreaterEqual = Radian{45} >= Radian{45};	// true
    constexpr bool operator>=(const Radian& lhs, const Degree& rhs); // bool isGreaterEqual = Radian{.5} >= Degree{60};	// false

    constexpr bool operator==(const Radian&, const Radian&); // bool isEqual = Radian{0.5} == Radian{0.5};	// true
    constexpr bool operator==(const Radian&, const Degree&); // bool isEqual = Radian{0.5} == Degree{60};	// false

    constexpr Radian operator-(const Radian&); // Degree angle = - Radian{0.5};				// Radian{-0.5}

    constexpr Radian operator+(Radian, const Radian&); // Radian angle = Radian{0.5} + Radian{0.5};	// Radian{1}
    constexpr Radian operator-(Radian, const Radian&); // Radian angle = Radian{0.5} - Radian{0.5};	// Radian{0}
    constexpr Radian operator*(Radian, float);         // Radian angle = Radian{0.5} * 3;				// Radian{1.5}
    constexpr Radian operator/(Radian, float);         // Radian angle = Radian{0.5} / 3;				// Radian{0.166...}

    /**
     * \brief Adds a radian string representation to an output stream
     * \param stream The output stream
     * \param radian The input radian
     * \return The modified stream
     */
    inline std::ostream& operator<<(std::ostream& stream, const Radian& radian);

    /**
     * \brief Parses a string representation from an input stream into radian
     * \param stream The input stream
     * \param radian The output radian
     * \return The modified stream
     */
    inline std::istream& operator>>(std::istream& stream, Radian& radian);

    inline namespace Literal
    {
        constexpr Radian operator""_rad(long double);            // Radian angle = 0.5_rad;
        constexpr Radian operator""_rad(unsigned long long int); // Radian angle = 1_rad;
    }
}

#include "Radian.inl"

#endif // !__LIBMATH__ANGLE__RADIAN_H__
