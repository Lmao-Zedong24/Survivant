#ifndef __LIBMATH__MATRIX__MATRIX4_H__
#define __LIBMATH__MATRIX__MATRIX4_H__

#include "TMatrix.h"
#include "ERotationOrder.h"

namespace LibMath
{
    class Radian;

    template <class T>
    class TVector3;

    template <class T>
    class TQuaternion;

    template <class DataT = float>
    constexpr TMatrix<4, 4, DataT> translation(DataT x, DataT y, DataT z);

    template <class DataT = float>
    constexpr TMatrix<4, 4, DataT> translation(const TVector3<DataT>& translation);

    template <class DataT = float>
    constexpr TMatrix<4, 4, DataT> scaling(DataT x, DataT y, DataT z);

    template <class DataT = float>
    constexpr TMatrix<4, 4, DataT> scaling(const TVector3<DataT>& scale);

    template <class DataT = float>
    constexpr TMatrix<4, 4, DataT> rotation(const Radian& angle, const TVector3<DataT>& axis);

    template <class DataT = float>
    constexpr TMatrix<4, 4, DataT> rotation(const Radian& yaw, const Radian& pitch, const Radian& roll);

    template <class DataT = float>
    constexpr TMatrix<4, 4, DataT> rotation(const TVector3<Radian>& angles);

    template <class DataT = float>
    constexpr TMatrix<4, 4, DataT> rotation(const TQuaternion<DataT>& quaternion);

    template <class DataT = float>
    constexpr TMatrix<4, 4, DataT> rotationEuler(const Radian& xAngle, const Radian& yAngle, const Radian& zAngle);

    template <class DataT = float>
    constexpr TMatrix<4, 4, DataT> rotationEuler(const TVector3<Radian>& angles);

    template <class DataT = float>
    constexpr TMatrix<4, 4, DataT> rotationFromTo(const TVector3<DataT>& from, const TVector3<DataT>& to);

    template <class DataT = float>
    constexpr TMatrix<4, 4, DataT>
    orthographicProjection(DataT left, DataT right, DataT bottom, DataT top, DataT zNear, DataT zFar);

    template <class DataT = float>
    constexpr TMatrix<4, 4, DataT> perspectiveProjection(const Radian& fovY, DataT aspect, DataT zNear, DataT zFar);

    template <class DataT = float>
    constexpr TMatrix<4, 4, DataT> lookAt(const TVector3<DataT>& eye, const TVector3<DataT>& center, const TVector3<DataT>& up);

    template <class DataT>
    constexpr TVector3<Radian> toEuler(const TMatrix<4, 4, DataT>& matrix, ERotationOrder rotationOrder);

    using Matrix4x2 = TMatrix<4, 2, float>;

    using Matrix4x3 = TMatrix<4, 3, float>;

    using Matrix4x4 = TMatrix<4, 4, float>;
    using Matrix4 = Matrix4x4;
}

#include "Matrix4.inl"

#ifdef __LIBMATH__VECTOR__VECTOR4_H__
#include "Matrix4Vector4Operation.h"
#endif // __LIBMATH__MATRIX_H__

#endif // !__LIBMATH__MATRIX__MATRIX4_H__
