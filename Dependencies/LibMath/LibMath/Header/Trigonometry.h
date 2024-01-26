#ifndef __LIBMATH__TRIGONOMETRY_H__
#define __LIBMATH__TRIGONOMETRY_H__

namespace LibMath
{
    class Radian;

    constexpr float g_pi = 3.14159265358979323846264338327950288f; // useful constant pi -> 3.141592...
    constexpr float g_rad2Deg = 180.f / g_pi;
    constexpr float g_deg2Rad = g_pi / 180.f;

    inline float sin(const Radian& angle); // float result = sin(Radian{0.5});		// 0.479426
    inline float cos(const Radian& angle); // float result = sin(Degree{45});		// 0.707107			// this make use implicit conversion
    inline float tan(const Radian& angle);
    // float result = sin(0.5_rad);			// 0.479426			// this make use user defined litteral from bellow
    constexpr Radian asin(float val);        // Radian angle = asin(0.479426);		// Radian{0.500001}
    constexpr Radian acos(float val);        // Degree angle = acos(0.707107);		// Degree{44.99998}	// this make use implicit conversion
    constexpr Radian atan(float val);        // Radian angle = atan(0.546302);		// Radian{0.500000}
    constexpr Radian atan(float y, float x); // Radian angle = atan(1, -2);			// Radian{2.677945}
}

#include "Trigonometry.inl"

#endif // !__LIBMATH__TRIGONOMETRY_H__
