#ifndef __LIBMATH__ANGLE__DEGREE_H__
#define __LIBMATH__ANGLE__DEGREE_H__
#include <iostream>

namespace LibMath
{
    class Radian;

    class Degree
    {
    public:
        constexpr          Degree();
        constexpr explicit Degree(float); // explicit so no ambiguous / implicit conversion from float to angle can happen
        constexpr          Degree(const Degree&);
        ~Degree() = default;

        constexpr operator Radian() const; // Radian angle = Degree{0.5};		// implicit conversion from Degree to Radian

        constexpr Degree& operator=(const Degree&);
        constexpr Degree& operator+=(const Degree&); // Degree angle += Degree{45};
        constexpr Degree& operator-=(const Degree&); // Degree angle -= Degree{45};
        constexpr Degree& operator*=(float);         // Degree angle *= 3;
        constexpr Degree& operator/=(float);         // Degree angle /= 3;

        constexpr void wrap(bool = false); // true -> limit m_value to range [-180, 180[	// false -> limit m_value to range [0, 360[

        constexpr float degree(bool = false) const;
        // return angle in degree	// true -> limit value to range [-180, 180[	// false -> limit value to range [0, 360[
        constexpr float radian(bool = true) const;
        // return angle in radian	// true -> limit value to range [-pi, pi[		// false -> limit value to range [0, 2 pi[
        constexpr float raw() const; // return m_angle

    private:
        float m_value;
    };

    constexpr bool operator<(const Degree& lhs, const Degree& rhs); // bool isLess = Degree{45} < Degree{365};	// true
    constexpr bool operator<(const Degree& lhs, const Radian& rhs); // bool isLess = Degree{60} < Radian{0.5};	// false

    constexpr bool operator<=(const Degree& lhs, const Degree& rhs); // bool isLessEqual = Degree{45} <= Degree{45};	// true
    constexpr bool operator<=(const Degree& lhs, const Radian& rhs); // bool isLessEqual = Degree{60} <= Radian{0.5};	// false

    constexpr bool operator>(const Degree& lhs, const Degree& rhs); // bool isGreater = Degree{45} > Degree{365};	// false
    constexpr bool operator>(const Degree& lhs, const Radian& rhs); // bool isGreater = Degree{60} > Radian{0.5};	// true

    constexpr bool operator>=(const Degree& lhs, const Degree& rhs); // bool isGreaterEqual = Degree{45} >= Degree{45};		// true
    constexpr bool operator>=(const Degree& lhs, const Radian& rhs); // bool isGreaterEqual = Degree{60} >= Radian{0.5};	// true

    constexpr bool operator==(const Degree&, const Degree&); // bool isEqual = Degree{45} == Degree{45};	// true
    constexpr bool operator==(const Degree&, const Radian&); // bool isEqual = Degree{60} == Radian{0.5};	// false

    constexpr Degree operator-(const Degree&); // Degree angle = - Degree{45};					// Degree{-45}

    constexpr Degree operator+(Degree, const Degree&); // Degree angle = Degree{45} + Degree{45};		// Degree{90}
    constexpr Degree operator-(Degree, const Degree&); // Degree angle = Degree{45} - Degree{45};		// Degree{0}
    constexpr Degree operator*(Degree, float);         // Degree angle = Degree{45} * 3;				// Degree{135}
    constexpr Degree operator/(Degree, float);         // Degree angle = Degree{45} / 3;				// Degree{15}

    /**
     * \brief Adds a degrees string representation to an output stream
     * \param stream The output stream
     * \param degrees The input degrees
     * \return The modified stream
     */
    inline std::ostream& operator<<(std::ostream& stream, const Degree& degrees);

    /**
     * \brief Parses a string representation from an input stream into degrees
     * \param stream The input stream
     * \param degrees The output degrees
     * \return The modified stream
     */
    inline std::istream& operator>>(std::istream& stream, Degree& degrees);

    inline namespace Literal
    {
        constexpr Degree operator""_deg(long double);            // Degree angle = 7.5_deg;
        constexpr Degree operator""_deg(unsigned long long int); // Degree angle = 45_deg;
    }
}

#include "Degree.inl"

#endif // !__LIBMATH__ANGLE__DEGREE_H__
