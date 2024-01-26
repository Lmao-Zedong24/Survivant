#ifndef __LIBMATH__TRIGONOMETRY_INL__
#define __LIBMATH__TRIGONOMETRY_INL__

#include <cmath>

#include "Trigonometry.h"

#include "Angle/Radian.h"

namespace LibMath
{
    inline float sin(const Radian& angle)
    {
        return sinf(angle.radian());
    }

    inline float cos(const Radian& angle)
    {
        return cosf(angle.radian());
    }

    inline float tan(const Radian& angle)
    {
        return tanf(angle.radian());
    }

    constexpr Radian asin(const float val)
    {
        return Radian(asinf(val));
    }

    constexpr Radian acos(const float val)
    {
        return Radian(acosf(val));
    }

    constexpr Radian atan(const float val)
    {
        return Radian(atanf(val));
    }

    constexpr Radian atan(const float y, const float x)
    {
        return Radian(atan2f(y, x));
    }
}

#endif // !__LIBMATH__TRIGONOMETRY_INL__
