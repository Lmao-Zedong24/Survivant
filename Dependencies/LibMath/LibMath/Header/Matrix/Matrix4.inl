#ifndef __LIBMATH__MATRIX__MATRIX4_INL__
#define __LIBMATH__MATRIX__MATRIX4_INL__

#include "Angle.h"
#include "Matrix4.h"
#include "Quaternion.h"
#include "Trigonometry.h"
#include "Vector/Vector3.h"

namespace LibMath
{
    template <class DataT>
    constexpr TMatrix<4, 4, DataT> translation(const DataT x, const DataT y, const DataT z)
    {
        TMatrix<4, 4, DataT> translationMatrix(1);

        translationMatrix(0, 3) = x;
        translationMatrix(1, 3) = y;
        translationMatrix(2, 3) = z;

        return translationMatrix;
    }

    template <class DataT>
    constexpr TMatrix<4, 4, DataT> translation(const TVector3<DataT>& translation)
    {
        return LibMath::translation(translation.m_x, translation.m_y, translation.m_z);
    }

    template <class DataT>
    constexpr TMatrix<4, 4, DataT> scaling(const DataT x, const DataT y, const DataT z)
    {
        TMatrix<4, 4, DataT> scalingMatrix;

        scalingMatrix(0, 0) = x;
        scalingMatrix(1, 1) = y;
        scalingMatrix(2, 2) = z;
        scalingMatrix(3, 3) = 1;

        return scalingMatrix;
    }

    template <class DataT>
    constexpr TMatrix<4, 4, DataT> scaling(const TVector3<DataT>& scale)
    {
        return scaling<DataT>(scale.m_x, scale.m_y, scale.m_z);
    }

    template <class DataT>
    constexpr TMatrix<4, 4, DataT> rotation(const Radian& angle, const TVector3<DataT>& axis)
    {
        const TVector3<DataT> dir = axis.normalized();
        const DataT           cos = LibMath::cos(angle);
        const DataT           sin = LibMath::sin(angle);

        TMatrix<4, 4, DataT> mat;

        mat(0, 0) = cos + dir.m_x * dir.m_x * (1 - cos);
        mat(0, 1) = dir.m_x * dir.m_y * (1 - cos) - dir.m_z * sin;
        mat(0, 2) = dir.m_x * dir.m_z * (1 - cos) + dir.m_y * sin;
        mat(0, 3) = 0;

        mat(1, 0) = dir.m_y * dir.m_x * (1 - cos) + dir.m_z * sin;
        mat(1, 1) = cos + dir.m_y * dir.m_y * (1 - cos);
        mat(1, 2) = dir.m_y * dir.m_z * (1 - cos) - dir.m_x * sin;
        mat(1, 3) = 0;

        mat(2, 0) = dir.m_z * dir.m_x * (1 - cos) - dir.m_y * sin;
        mat(2, 1) = dir.m_z * dir.m_y * (1 - cos) + dir.m_x * sin;
        mat(2, 2) = cos + dir.m_z * dir.m_z * (1 - cos);
        mat(2, 3) = 0;

        mat(3, 0) = 0;
        mat(3, 1) = 0;
        mat(3, 2) = 0;
        mat(3, 3) = 1;

        return mat;
    }

    template <class DataT>
    constexpr TMatrix<4, 4, DataT> rotation(const Radian& yaw, const Radian& pitch, const Radian& roll)
    {
        const DataT cosYaw = cos(yaw);
        const DataT sinYaw = sin(yaw);

        const DataT cosPitch = cos(pitch);
        const DataT sinPitch = sin(pitch);

        const DataT cosRoll = cos(roll);
        const DataT sinRoll = sin(roll);

        TMatrix<4, 4, DataT> rotationMat;

        rotationMat(0, 0) = cosYaw * cosRoll + sinYaw * sinPitch * sinRoll;
        rotationMat(0, 1) = -cosYaw * sinRoll + sinYaw * sinPitch * cosRoll;
        rotationMat(0, 2) = sinYaw * cosPitch;
        rotationMat(0, 3) = 0;

        rotationMat(1, 0) = sinRoll * cosPitch;
        rotationMat(1, 1) = cosRoll * cosPitch;
        rotationMat(1, 2) = -sinPitch;
        rotationMat(1, 3) = 0;

        rotationMat(2, 0) = -sinYaw * cosRoll + cosYaw * sinPitch * sinRoll;
        rotationMat(2, 1) = sinRoll * sinYaw + cosYaw * sinPitch * cosRoll;
        rotationMat(2, 2) = cosYaw * cosPitch;
        rotationMat(2, 3) = 0;

        rotationMat(3, 0) = 0;
        rotationMat(3, 1) = 0;
        rotationMat(3, 2) = 0;
        rotationMat(3, 3) = 1;

        return rotationMat;
    }

    template <class DataT>
    constexpr TMatrix<4, 4, DataT> rotation(const TVector3<Radian>& angles)
    {
        return rotation<DataT>(angles.m_x, angles.m_y, angles.m_z);
    }

    template <class DataT>
    constexpr TMatrix<4, 4, DataT> rotation(const TQuaternion<DataT>& quaternion)
    {
        TMatrix<4, 4, DataT> mat(static_cast<DataT>(1));

        DataT xSqr = quaternion.m_x * quaternion.m_x;
        DataT ySqr = quaternion.m_y * quaternion.m_y;
        DataT zSqr = quaternion.m_z * quaternion.m_z;

        DataT wx = quaternion.m_w * quaternion.m_x;
        DataT wy = quaternion.m_w * quaternion.m_y;
        DataT wz = quaternion.m_w * quaternion.m_z;

        DataT xy = quaternion.m_x * quaternion.m_y;
        DataT xz = quaternion.m_x * quaternion.m_z;

        DataT yz = quaternion.m_y * quaternion.m_z;

        mat(0, 0) = static_cast<DataT>(1) - static_cast<DataT>(2) * (ySqr + zSqr);
        mat(0, 1) = static_cast<DataT>(2) * (xy - wz);
        mat(0, 2) = static_cast<DataT>(2) * (xz + wy);

        mat(1, 0) = static_cast<DataT>(2) * (xy + wz);
        mat(1, 1) = static_cast<DataT>(1) - static_cast<DataT>(2) * (xSqr + zSqr);
        mat(1, 2) = static_cast<DataT>(2) * (yz - wx);

        mat(2, 0) = static_cast<DataT>(2) * (xz - wy);
        mat(2, 1) = static_cast<DataT>(2) * (yz + wx);
        mat(2, 2) = static_cast<DataT>(1) - static_cast<DataT>(2) * (xSqr + ySqr);

        return mat;
    }

    template <class DataT>
    constexpr TMatrix<4, 4, DataT> rotationEuler(const Radian& xAngle, const Radian& yAngle,
                                                 const Radian& zAngle)
    {
        return rotation<DataT>(zAngle, xAngle, yAngle);
    }

    template <class DataT>
    constexpr TMatrix<4, 4, DataT> rotationEuler(const TVector3<Radian>& angles)
    {
        return rotationEuler<DataT>(angles.m_x, angles.m_y, angles.m_z);
    }

    // Adapted from https://gist.github.com/kevinmoran/b45980723e53edeb8a5a43c49f134724
    template <class DataT>
    constexpr TMatrix<4, 4, DataT> rotationFromTo(const TVector3<DataT>& from, const TVector3<DataT>& to)
    {
        const auto& fromDir = from.normalized();
        const auto& toDir = to.normalized();

        if (toDir == fromDir)
            return TMatrix<4, 4, DataT>(1);

        if (toDir == -fromDir)
            return scaling<DataT>(-1, -1, -1);

        const TVector3<DataT> axis = from.cross(to);

        const DataT cosA = from.dot(to);
        const DataT k = static_cast<DataT>(1) / (static_cast<DataT>(1) + cosA);

        TMatrix<4, 4, DataT> rotationMat;

        rotationMat(0, 0) = (axis.m_x * axis.m_x * k) + cosA;
        rotationMat(0, 1) = (axis.m_y * axis.m_x * k) - axis.m_z;
        rotationMat(0, 2) = (axis.m_z * axis.m_x * k) + axis.m_y;
        rotationMat(0, 3) = static_cast<DataT>(0);

        rotationMat(1, 0) = (axis.m_x * axis.m_y * k) + axis.m_z;
        rotationMat(1, 1) = (axis.m_y * axis.m_y * k) + cosA;
        rotationMat(1, 2) = (axis.m_z * axis.m_y * k) - axis.m_x;
        rotationMat(1, 3) = static_cast<DataT>(0);

        rotationMat(2, 0) = (axis.m_x * axis.m_z * k) - axis.m_y;
        rotationMat(2, 1) = (axis.m_y * axis.m_z * k) + axis.m_x;
        rotationMat(2, 2) = (axis.m_z * axis.m_z * k) + cosA;
        rotationMat(2, 3) = static_cast<DataT>(0);

        rotationMat(3, 0) = static_cast<DataT>(0);
        rotationMat(3, 1) = static_cast<DataT>(0);
        rotationMat(3, 2) = static_cast<DataT>(0);
        rotationMat(3, 3) = static_cast<DataT>(1);

        return rotationMat;
    }

    template <class DataT>
    constexpr TMatrix<4, 4, DataT> orthographicProjection(const DataT left, const DataT   right,
                                                          const DataT bottom, const DataT top, const DataT zNear, const DataT zFar)
    {
        TMatrix<4, 4, DataT> mat;

        mat(0, 0) = static_cast<DataT>(2) / (right - left);
        mat(0, 3) = (right + left) / (left - right);

        mat(1, 1) = static_cast<DataT>(2) / (top - bottom);
        mat(1, 3) = (top + bottom) / (bottom - top);

        mat(2, 2) = static_cast<DataT>(2) / (zNear - zFar);
        mat(2, 3) = (zFar + zNear) / (zNear - zFar);

        mat(3, 3) = static_cast<DataT>(1);

        return mat;
    }

    template <class DataT>
    constexpr TMatrix<4, 4, DataT> perspectiveProjection(const Radian& fovY,
                                                         const DataT   aspect, const DataT zNear, const DataT zFar)
    {
        const DataT tanHalfFovY = tan(fovY * .5f);

        TMatrix<4, 4, DataT> mat;

        mat(0, 0) = static_cast<DataT>(1) / (aspect * tanHalfFovY);
        mat(1, 1) = static_cast<DataT>(1) / tanHalfFovY;
        mat(2, 2) = (zFar + zNear) / (zNear - zFar);
        mat(2, 3) = (static_cast<DataT>(2) * zFar * zNear) / (zNear - zFar);
        mat(3, 2) = static_cast<DataT>(-1);

        return mat;
    }

    template <class DataT>
    constexpr TMatrix<4, 4, DataT> lookAt(const TVector3<DataT>& eye, const TVector3<DataT>& center,
                                          const TVector3<DataT>& up)
    {
        const TVector3<DataT> f = (center - eye).normalized();
        const TVector3<DataT> s = f.cross(up).normalized();
        const TVector3<DataT> u = s.cross(f);

        TMatrix<4, 4, DataT> mat;

        mat(0, 0) = s.m_x;
        mat(0, 1) = s.m_y;
        mat(0, 2) = s.m_z;
        mat(0, 3) = -s.dot(eye);

        mat(1, 0) = u.m_x;
        mat(1, 1) = u.m_y;
        mat(1, 2) = u.m_z;
        mat(1, 3) = -u.dot(eye);

        mat(2, 0) = -f.m_x;
        mat(2, 1) = -f.m_y;
        mat(2, 2) = -f.m_z;
        mat(2, 3) = f.dot(eye);

        mat(3, 3) = 1;

        return mat;
    }

    template <class DataT>
    constexpr TVector3<Radian> toEuler(const TMatrix<4, 4, DataT>& matrix, const ERotationOrder rotationOrder)
    {
        using T = floating_t<DataT>;
        TVector3<Radian> angles;

        switch (rotationOrder)
        {
        case ERotationOrder::XYZ:
        {
            angles.m_x = -atan(matrix(1, 2), matrix(2, 2));

            const T c2 = squareRoot(matrix(0, 0) * matrix(0, 0) + matrix(0, 1) * matrix(0, 1));
            angles.m_y = -atan(-matrix(0, 2), c2);

            const T s1 = sin(-angles.m_x);
            const T c1 = cos(-angles.m_x);
            angles.m_z = -atan(s1 * matrix(2, 0) - c1 * matrix(1, 0), c1 * matrix(1, 1) - s1 * matrix(2, 1));
            break;
        }
        case ERotationOrder::XZY:
        {
            angles.m_x = atan(matrix(2, 1), matrix(1, 1));

            T c2 = squareRoot(matrix(0, 0) * matrix(0, 0) + matrix(0, 2) * matrix(0, 2));
            angles.m_z = atan(-matrix(0, 1), c2);

            T s1 = sin(angles.m_x);
            T c1 = cos(angles.m_x);
            angles.m_y = atan(s1 * matrix(1, 0) - c1 * matrix(2, 0), c1 * matrix(2, 2) - s1 * matrix(1, 2));
            break;
        }
        case ERotationOrder::YXZ:
        {
            angles.m_y = atan(matrix(0, 2), matrix(2, 2));

            const T c2 = squareRoot(matrix(1, 0) * matrix(1, 0) + matrix(1, 1) * matrix(1, 1));
            angles.m_x = atan(-matrix(1, 2), c2);

            const T s1 = sin(angles.m_y);
            const T c1 = cos(angles.m_y);
            angles.m_z = atan(s1 * matrix(2, 1) - c1 * matrix(0, 1), c1 * matrix(0, 0) - s1 * matrix(2, 0));

            break;
        }
        case ERotationOrder::YZX:
        {
            angles.m_y = atan(-matrix(2, 0), matrix(0, 0));

            T c2 = squareRoot(matrix(1, 1) * matrix(1, 1) + matrix(1, 2) * matrix(1, 2));
            angles.m_z = atan(matrix(1, 0), c2);

            T s1 = sin(angles.m_y);
            T c1 = cos(angles.m_y);
            angles.m_x = atan(s1 * matrix(0, 1) + c1 * matrix(2, 1), s1 * matrix(0, 2) + c1 * matrix(2, 2));
            break;
        }
        case ERotationOrder::ZXY:
        {
            angles.m_z = atan(-matrix(0, 1), matrix(1, 1));

            T c2 = squareRoot(matrix(2, 0) * matrix(2, 0) + matrix(2, 2) * matrix(2, 2));
            angles.m_x = atan(matrix(2, 1), c2);

            T s1 = sin(angles.m_z);
            T c1 = cos(angles.m_z);
            angles.m_y = atan(c1 * matrix(0, 2) + s1 * matrix(1, 2), c1 * matrix(0, 0) + s1 * matrix(1, 0));
            break;
        }
        case ERotationOrder::ZYX:
        {
            angles.m_z = atan(matrix(1, 0), matrix(0, 0));

            T c2 = squareRoot(matrix(2, 1) * matrix(2, 1) + matrix(2, 2) * matrix(2, 2));
            angles.m_y = atan(-matrix(2, 0), c2);

            T s1 = sin(angles.m_z);
            T c1 = cos(angles.m_z);
            angles.m_x = atan(s1 * matrix(0, 2) - c1 * matrix(1, 2), c1 * matrix(1, 1) - s1 * matrix(0, 1));
            break;
        }
        }

        return angles;
    }
}

#endif // !__LIBMATH__MATRIX__MATRIX4_INL__
