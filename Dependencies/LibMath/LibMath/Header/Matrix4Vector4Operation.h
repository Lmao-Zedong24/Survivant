#ifndef __LIBMATH__MATRIX4VECTOR4OPERATION_H_
#define __LIBMATH__MATRIX4VECTOR4OPERATION_H_

#include "Vector/Vector4.h"
#include "Matrix/Matrix4.h"

namespace LibMath
{
    template <class T, class U>
    TVector4<U> operator*(const TMatrix<4, 4, T>& operation, const TVector4<U>& operand)
    {
        TMatrix<4, 1, T> vec4Mat;
        vec4Mat[0] = static_cast<T>(operand.m_x);
        vec4Mat[1] = static_cast<T>(operand.m_y);
        vec4Mat[2] = static_cast<T>(operand.m_z);
        vec4Mat[3] = static_cast<T>(operand.m_w);

        vec4Mat = operation * vec4Mat;
        return { static_cast<U>(vec4Mat[0]), static_cast<U>(vec4Mat[1]), static_cast<U>(vec4Mat[2]), static_cast<U>(vec4Mat[3]) };
    }
}

#endif // !__LIBMATH__MATRIX4VECTOR4OPERATION_H_
