#ifndef __LIBMATH__INTERPOLATION_H__
#define __LIBMATH__INTERPOLATION_H__

#include "Trigonometry.h"
#include "Angle/Radian.h"

namespace LibMath
{
    template <typename ValT, typename ProgressT>
    constexpr ValT lerp(const ValT from, const ValT to, const ProgressT alpha)
    {
        return from + (to - from) * alpha;
    }

    template <typename ValT, typename ProgressT>
    constexpr ValT slerp(ValT from, ValT to, const ProgressT alpha)
    {
        const Radian angle = acos(from.dot(to));
        const float  invSinAngle = 1.f / sin(angle);

        from *= sin(angle * (static_cast<ProgressT>(1) - alpha));
        to *= sin(angle * alpha);

        return (from + to) * invSinAngle;
    }
}

#endif // !__LIBMATH__INTERSECTION_H__
