#ifndef __LIBMATH__QUATERNION_H__
#define __LIBMATH__QUATERNION_H__

#include <type_traits>

#include "ERotationOrder.h"
#include "Interpolation.h"

#include "Angle/Radian.h"
#include "Matrix/Matrix4.h"
#include "Vector/Vector3.h"

namespace LibMath
{
    template <class T>
    class TQuaternion
    {
        static_assert(std::is_floating_point_v<T>, "Invalid quaternion - Data type should be a floating point type");

    public:
        static constexpr TQuaternion identity();

        T m_x = 0;
        T m_y = 0;
        T m_z = 0;
        T m_w = 0;

        constexpr TQuaternion() = default;

        /**
         * \brief Creates a quaternion with all components set to the given value
         * \param value The quaternion's components value
         */
        explicit constexpr TQuaternion(T value);

        /**
         * \brief Creates a quaternion with the given component values
         * \param w The quaternion's w component
         * \param x The quaternion's x component
         * \param y The quaternion's y component
         * \param z The quaternion's z component
         */
        constexpr TQuaternion(T w, T x, T y, T z);

        /**
         * \brief Creates a quaternion with the given scalar and vector parts
         * \param scalar The quaternion's w component
         * \param vector The quaternion's x, y and z components
         */
        template <typename U>
        constexpr TQuaternion(T scalar, TVector3<U> vector);

        /**
         * \brief Creates a quaternion from the given axis and angle
         * \tparam U The axis vector's data type
         * \param angle The rotation angle
         * \param axis The rotation axis
         */
        template <typename U>
        constexpr TQuaternion(Radian angle, TVector3<U> axis);

        /**
         * \brief Creates a quaternion from the given angles
         * \param yaw The yaw angle
         * \param pitch The pitch angle
         * \param roll The roll angle
         */
        constexpr TQuaternion(Radian yaw, Radian pitch, Radian roll);

        /**
         * \brief Creates a quaternion from the given rotation angles (x=yaw, y=pitch, z=roll)
         * \param angles The rotation angles vector
         */
        explicit constexpr TQuaternion(const TVector3<Radian>& angles);

        /**
         * \brief Creates a quaternion from the given rotation matrix
         * \tparam U The rotation matrix's data type
         * \param rotationMatrix The rotation matrix
         */
        template <typename U>
        explicit constexpr TQuaternion(const TMatrix<3, 3, U>& rotationMatrix);

        /**
         * \brief Creates a quaternion from the given rotation matrix
         * \tparam U The rotation matrix's data type
         * \param rotationMatrix The rotation matrix
         */
        template <typename U>
        explicit constexpr TQuaternion(const TMatrix<4, 4, U>& rotationMatrix);

        /**
         * \brief Creates a copy of the given quaternion
         * \tparam U The copied quaternion's data type
         * \param other The copied quaternion
         */
        template <typename U>
        constexpr TQuaternion(const TQuaternion<U>& other);

        /**
         * \brief Creates a move copy of the given quaternion
         * \tparam U The moved quaternion's data type
         * \param other The moved quaternion
         */
        template <typename U>
        constexpr TQuaternion(TQuaternion<U>&& other) noexcept;

        /**
         * \brief Assigns a copy of the given quaternion to the current one
         * \tparam U The copied quaternion's data type
         * \param other The copied quaternion
         * \return The modified quaternion
         */
        template <typename U>
        constexpr TQuaternion& operator=(const TQuaternion<U>& other);

        /**
         * \brief Assigns a move copy of the given quaternion to the current one
         * \tparam U The moved quaternion's data type
         * \param other The moved quaternion
         * \return The modified quaternion
         */
        template <typename U>
        constexpr TQuaternion& operator=(TQuaternion<U>&& other) noexcept;

        /**
         * \brief Creates a quaternion from the given euler angles
         * \param x The x angle
         * \param y The y angle
         * \param z The z angle
         * \param rotationOrder The rotation application order
         */
        static constexpr TQuaternion fromEuler(const Radian& x, const Radian& y, const Radian& z, ERotationOrder rotationOrder);

        /**
         * \brief Creates a quaternion from the given euler angles vector
         * \param angles The euler angles vector
         * \param rotationOrder The rotation application order
         */
        static constexpr TQuaternion fromEuler(const TVector3<Radian>& angles, ERotationOrder rotationOrder);

        /**
         * \brief Computes the quaternion representing the rotation from the origin vector to the destination vector
         * \tparam U The vectors' data type
         * \param from The origin vector
         * \param to The destination vector
         * \return The quaternion representing the rotation from the origin vector to the destination vector
         */
        template <class U>
        static constexpr TQuaternion fromTo(const TVector3<U>& from, const TVector3<U>& to);

        /**
         * \brief Computes a euler representation of the quaternion (x = yaw, y = pitch, z = roll)
         * \return A euler representation of the quaternion
         */
        constexpr TVector3<Radian> toYawPitchRoll() const;

        /**
         * \brief Computes a euler representation of the quaternion
         * \param rotationOrder The rotation application order
         * \return A euler representation of the quaternion
         */
        constexpr TVector3<Radian> toEuler(ERotationOrder rotationOrder) const;

        /**
         * \brief Converts the quaternion to an angle/axis representation
         * \tparam U The axis' data type
         * \param angle The output angle variable
         * \param axis The output axis variable
         */
        template <typename U>
        constexpr void toAngleAxis(Radian& angle, TVector3<U>& axis) const;

        /**
         * \brief Extracts the vector part of the quaternion
         */
        constexpr operator TVector3<T>() const;

        /**
         * \brief Gets the quaternion's component at the given index (0/'x', 1/'y', 2/'z', 3/'w')
         * \param index The component index
         * \return The component at the given index
         */
        [[nodiscard]] constexpr T& operator[](int index);

        /**
         * \brief Gets the quaternion's component at the given index (0/'x', 1/'y', 2/'z', 3/'w')
         * \param index The component index
         * \return The component at the given index
         */
        [[nodiscard]] constexpr T operator[](int index) const;

        /**
         * \brief Adds the given quaternion to the current one
         * \tparam U The other quaternion's data type
         * \param other The quaternion to add to this one
         * \return A reference to the modified quaternion
         */
        template <typename U>
        constexpr TQuaternion& operator+=(const TQuaternion<U>& other);

        /**
         * \brief Subtracts the given quaternion from the current one
         * \tparam U The other quaternion's data type
         * \param other The quaternion to subtract from this one
         * \return A reference to the modified quaternion
         */
        template <typename U>
        constexpr TQuaternion& operator-=(const TQuaternion<U>& other);

        /**
         * \brief Multiplies the current quaternion by the given one
         * \tparam U The other quaternion's data type
         * \param other The quaternion to multiply this one by
         * \return A reference to the modified quaternion
         */
        template <typename U>
        constexpr TQuaternion& operator*=(const TQuaternion<U>& other);

        /**
         * \brief "Divides" the current quaternion by the given one
         * \tparam U The other quaternion's data type
         * \param other The quaternion to "divide" this one by
         * \return A reference to the modified quaternion
         */
        template <typename U>
        constexpr TQuaternion& operator/=(const TQuaternion<U>& other);

        /**
         * \brief Adds the given value to the quaternion's real part
         * \tparam U The value's data type
         * \param value The value to add
         * \return A reference to the modified quaternion
         */
        template <typename U>
        constexpr TQuaternion& operator+=(U value);

        /**
         * \brief Subtracts the given value from the quaternion's real part
         * \tparam U The value's data type
         * \param value The value to subtract
         * \return A reference to the modified quaternion
         */
        template <typename U>
        constexpr TQuaternion& operator-=(U value);

        /**
         * \brief Multiplies the current quaternion by the given scalar
         * \tparam U The scalar's data type
         * \param scalar The scalar to multiply by
         * \return A reference to the modified quaternion
         */
        template <typename U>
        constexpr TQuaternion& operator*=(U scalar);

        /**
         * \brief Divides the current quaternion by the given scalar
         * \tparam U The scalar's data type
         * \param scalar The scalar to divide by
         * \return A reference to the modified quaternion
         */
        template <typename U>
        constexpr TQuaternion& operator/=(U scalar);

        /**
         * \brief Gets the quaternion as an array
         * \return A pointer to the start of the quaternion
         */
        [[nodiscard]] constexpr T* getArray();

        /**
         * \brief Gets the quaternion as an array
         * \return A pointer to the start of the quaternion
         */
        [[nodiscard]] constexpr const T* getArray() const;

        /**
         * \brief Checks if the quaternion's magnitude is 1
         * \return True if the quaternion is a unit quaternion. False otherwise
         */
        [[nodiscard]] constexpr bool isUnit() const;

        /**
         * \brief Computes the quaternion's magnitude
         * \return The quaternion's magnitude
         */
        [[nodiscard]] constexpr T magnitude() const;

        /**
         * \brief Computes the quaternion's square magnitude
         * \return The quaternion's squared magnitude
         */
        [[nodiscard]] constexpr T magnitudeSquared() const;

        /**
         * \brief Computes the dot product of two quaternions
         * \tparam U The other quaternion's data type
         * \param other The other quaternion
         * \return The dot product of the two quaternions
         */
        template <typename U>
        [[nodiscard]] constexpr T dot(const TQuaternion<U>& other) const;

        /**
         * \brief Computes the quaternion's conjugate
         * \return The quaternion's conjugate
         */
        [[nodiscard]] constexpr TQuaternion conjugate() const;

        /**
         * \brief Computes the quaternion's inverse
         * \return The quaternion's inverse
         */
        [[nodiscard]] constexpr TQuaternion inverse() const;

        /**
         * \brief Normalizes the quaternion
         */
        constexpr void normalize();

        /**
         * \brief Returns a normalized copy of the quaternion
         * \return The normalized quaternion
         */
        [[nodiscard]] constexpr TQuaternion normalized() const;

        /**
         * \brief Gets a string representation of this quaternion
         * \return The string representation of this quaternion
         */
        [[nodiscard]] constexpr std::string string() const;

        /**
         * \brief Gets a long string representation of this quaternion
         * \return The verbose string representation of this quaternion
         */
        [[nodiscard]] constexpr std::string stringLong() const;
    };

    /**
     * \brief Checks whether two quaternions have the same components
     * \tparam T The left quaternion's data type
     * \tparam U The right quaternion's data type
     * \param left The left quaternion
     * \param right The right quaternion
     * \return True if the quaternions are equal. False otherwise
     */
    template <class T, class U>
    constexpr bool operator==(const TQuaternion<T>& left, const TQuaternion<U>& right);

    /**
     * \brief Checks whether two quaternions have different components
     * \tparam T The left quaternion's data type
     * \tparam U The right quaternion's data type
     * \param left The left quaternion
     * \param right The right quaternion
     * \return True if the quaternions are not equal. False otherwise
     */
    template <class T, class U>
    constexpr bool operator!=(const TQuaternion<T>& left, const TQuaternion<U>& right);

    /**
     * \brief Checks whether the left quaternion's magnitude is greater than the right quaternion's magnitude
     * \tparam T The left quaternion's data type
     * \tparam U The right quaternion's data type
     * \param left The left quaternion
     * \param right The right quaternion
     * \return True if the left quaternion has a greater magnitude. False otherwise
     */
    template <class T, class U>
    constexpr bool operator>(const TQuaternion<T>& left, const TQuaternion<U>& right);

    /**
     * \brief Checks whether the left quaternion's magnitude is smaller than the right quaternion's magnitude
     * \tparam T The left quaternion's data type
     * \tparam U The right quaternion's data type
     * \param left The left quaternion
     * \param right The right quaternion
     * \return True if the left quaternion has a smaller magnitude. False otherwise
     */
    template <class T, class U>
    constexpr bool operator<(const TQuaternion<T>& left, const TQuaternion<U>& right);

    /**
     * \brief Checks whether the left quaternion's magnitude is greater than or equal to the right quaternion's magnitude
     * \tparam T The left quaternion's data type
     * \tparam U The right quaternion's data type
     * \param left The left quaternion
     * \param right The right quaternion
     * \return True if the left quaternion has a greater or equal magnitude. False otherwise
     */
    template <class T, class U>
    constexpr bool operator>=(const TQuaternion<T>& left, const TQuaternion<U>& right);

    /**
     * \brief Checks whether the left quaternion's magnitude is smaller than or equal to the right quaternion's magnitude
     * \tparam T The left quaternion's data type
     * \tparam U The right quaternion's data type
     * \param left The left quaternion
     * \param right The right quaternion
     * \return True if the left quaternion has a smaller or equal magnitude. False otherwise
     */
    template <class T, class U>
    constexpr bool operator<=(const TQuaternion<T>& left, const TQuaternion<U>& right);

    /**
     * \brief Creates a copy of the given quaternion with all its components inverted
     * \tparam T The quaternion's data type
     * \param quat The source quaternion
     * \return A copy of the quaternion with all its components inverted
     */
    template <class T>
    constexpr TQuaternion<T> operator-(const TQuaternion<T>& quat);

    /**
     * \brief Adds the right quaternion to the left one
     * \tparam T The left quaternion's data type
     * \tparam U The right quaternion's data type
     * \param left The left quaternion
     * \param right The right quaternion
     * \return The sum of the left and right quaternions
     */
    template <class T, class U>
    constexpr TQuaternion<T> operator+(TQuaternion<T> left, const TQuaternion<U>& right);

    /**
     * \brief Subtract the right quaternion from the left one
     * \tparam T The left quaternion's data type
     * \tparam U The right quaternion's data type
     * \param left The left quaternion
     * \param right The right quaternion
     * \return The difference of the left and right quaternions
     */
    template <class T, class U>
    constexpr TQuaternion<T> operator-(TQuaternion<T> left, const TQuaternion<U>& right);

    /**
     * \brief Multiplies the left quaternion by the right one
     * \tparam T The left quaternion's data type
     * \tparam U The right quaternion's data type
     * \param left The left quaternion
     * \param right The right quaternion
     * \return The left quaternion multiplied by the right quaternion
     */
    template <class T, class U>
    constexpr TQuaternion<T> operator*(TQuaternion<T> left, const TQuaternion<U>& right);

    /**
     * \brief Divides the left quaternion by the right one
     * \tparam T The left quaternion's data type
     * \tparam U The right quaternion's data type
     * \param left The left quaternion
     * \param right The right quaternion
     * \return The left quaternion divided by the right quaternion
     */
    template <class T, class U>
    constexpr TQuaternion<T> operator/(TQuaternion<T> left, const TQuaternion<U>& right);

    /**
     * \brief Adds a value to the real part of a quaternion
     * \tparam T The quaternion's data type
     * \tparam U The value's data type
     * \param value The value to add
     * \param quat The quaternion to add the value to
     * \return The quaternion with the value added to it's real part
     */
    template <class T, class U>
    constexpr TQuaternion<T> operator+(TQuaternion<T> quat, U value);

    /**
     * \brief Subtracts a value from the real part of a quaternion
     * \tparam T The quaternion's data type
     * \tparam U The value's data type
     * \param value The value to subtract
     * \param quat The quaternion to subtract the value from
     * \return The quaternion with the value subtracted from it's real part
     */
    template <class T, class U>
    constexpr TQuaternion<T> operator-(TQuaternion<T> quat, U value);

    /**
     * \brief Multiplies the given quaternion by a scalar
     * \tparam T The quaternion's data type
     * \tparam U The scalar's data type
     * \param scalar The scalar to multiply by
     * \param quat The quaternion to multiply
     * \return The quaternion multiplied by the scalar
     */
    template <class T, class U>
    constexpr TQuaternion<T> operator*(TQuaternion<T> quat, U scalar);

    /**
     * \brief Multiplies the given quaternion by a scalar
     * \tparam T The quaternion's data type
     * \tparam U The scalar's data type
     * \param scalar The scalar to multiply by
     * \param quat The quaternion to multiply
     * \return The quaternion multiplied by the scalar
     */
    template <class T, class U>
    constexpr TQuaternion<U> operator*(U scalar, TQuaternion<T> quat);

    /**
     * \brief Divides the given quaternion by a scalar
     * \tparam T The quaternion's data type
     * \tparam U The scalar's data type
     * \param scalar The scalar to divide by
     * \param quat The quaternion to divide
     * \return The quaternion divided by the scalar
     */
    template <class T, class U>
    constexpr TQuaternion<T> operator/(TQuaternion<T> quat, U scalar);

    /**
     * \brief Adds a quaternion's string representation to an output stream
     * \tparam T The quaternion's data type
     * \param stream The output stream
     * \param quat The quaternion
     * \return The modified stream
     */
    template <class T>
    constexpr std::ostream& operator<<(std::ostream& stream, const TQuaternion<T>& quat);

    /**
     * \brief Parses a string representation from an input stream into a quaternion
     * \tparam T The quaternion's data type
     * \param stream The input stream
     * \param quat The output quaternion
     * \return The modified stream
     */
    template <class T>
    constexpr std::istream& operator>>(std::istream& stream, TQuaternion<T>& quat);

#define QUAT_ALIAS_IMPL(DataType, Alias)                               \
    using Alias = TQuaternion<DataType>;                               \
                                                                       \
    template<>                                                         \
    constexpr Alias slerp(Alias from, Alias to, DataType alpha)        \
    {                                                                  \
         DataType cosAngle = from.dot(to);                             \
                                                                       \
         if (cosAngle < DataType(0))                                   \
         {                                                             \
             cosAngle = -cosAngle;                                     \
             to = Alias(-to.m_w, -to.m_x, -to.m_y, -to.m_z);           \
         }                                                             \
                                                                       \
         if (cosAngle > DataType(.99985)) /* ~1deg */                  \
             return lerp(from, to, alpha).normalized();                \
                                                                       \
         const Radian angle = acos(static_cast<float>(cosAngle));      \
         const DataType invSinAngle = DataType(1) / sin(angle);        \
                                                                       \
         from *= sin(angle * static_cast<float>(DataType(1) - alpha)); \
         to *= sin(angle * static_cast<float>(alpha));                 \
                                                                       \
         return (from + to) * invSinAngle;                             \
    }

    QUAT_ALIAS_IMPL(float, Quaternion);
    QUAT_ALIAS_IMPL(double, QuaternionD);
}

#include "Quaternion.inl"

#endif // !__LIBMATH__QUATERNION_H__
