#ifndef __LIBMATH__VECTOR__VECTOR3_H__
#define __LIBMATH__VECTOR__VECTOR3_H__

#include <iostream>
#include <string>

#include "Arithmetic.h"

#include "Angle/Radian.h"

namespace LibMath
{
    template <class T>
    class TQuaternion;

    template <class T>
    class TVector3
    {
        static_assert(std::is_arithmetic_v<T> || std::is_same_v<T, Degree> || std::is_same_v<T, Radian>,
            "Invalid vector - Data type should be an arithmetic or angle type");

    public:
        /**
         * \brief Returns a vector with all its components set to 0
         */
        static TVector3 zero();

        /**
         * \brief Returns a vector with all its components set to 1
         */
        static TVector3 one();

        /**
         * \brief Returns a vector pointing upward
         */
        static TVector3 up();

        /**
         * \brief Returns a vector pointing downward
         */
        static TVector3 down();

        /**
         * \brief Returns a vector pointing left
         */
        static TVector3 left();

        /**
         * \brief Returns a vector pointing right
         */
        static TVector3 right();

        /**
         * \brief Returns a vector pointing forward
         */
        static TVector3 front();

        /**
         * \brief Returns a vector pointing backward
         */
        static TVector3 back();

        /**
         * \brief Creates a default vector
         */
        TVector3() = default;

        /**
         * \brief Creates a vector with the given value for all its components
         * \param value The vector's components value
         */
        explicit TVector3(T value);

        /**
         * \brief Creates a vector with the given component values
         * \param x The vector's x value
         * \param y The vector's y value
         * \param z The vector's z value
         */
        TVector3(T x, T y, T z);

        /**
         * \brief Creates a copy of the given vector
         * \tparam U The copied vector's data type
         * \param other The copied vector
         */
        template <class U>
        TVector3(const TVector3<U>& other);

        /**
         * \brief Creates a move copy of the given vector
         * \tparam U The moved vector's data type
         * \param other The moved vector
         */
        template <class U>
        TVector3(TVector3<U>&& other);

        /**
         * \brief Destroys the vector
         */
        ~TVector3() = default;

        /**
         * \brief Assigns a copy of the given vector to the current one
         * \tparam U The copied vector's data type
         * \param other The copied vector
         * \return The modified vector
         */
        template <class U>
        TVector3& operator=(const TVector3<U>& other);

        /**
         * \brief Assigns a move copy of the given vector to the current one
         * \tparam U The moved vector's data type
         * \param other The moved vector
         * \return The modified vector
         */
        template <class U>
        TVector3& operator=(TVector3<U>&& other);

        /**
         * \brief Gets the vector's component at the given index (0/'x', 1/'y', 2/'z')
         * \param index The component's index
         * \return The component at the given index
         */
        T& operator[](int index);

        /**
         * \brief Gets the vector's component at the given index (0/'x', 1/'y', 2/'z')
         * \param index The component's index
         * \return The component at the given index
         */
        T operator[](int index) const;

        /**
         * \brief Adds the given vector to the current one
         * \tparam U The other vector's data type
         * \param other The vector to add to this one
         * \return A reference to the modified vector
         */
        template <class U>
        TVector3& operator+=(const TVector3<U>& other);

        /**
         * \brief Subtracts the given vector from the current one
         * \tparam U The other vector's data type
         * \param other The vector to subtract from this one
         * \return A reference to the modified vector
         */
        template <class U>
        TVector3& operator-=(const TVector3<U>& other);

        /**
         * \brief Multiplies the current vector by the given one
         * \tparam U The other vector's data type
         * \param other The vector to multiply this one by
         * \return A reference to the modified vector
         */
        template <class U>
        TVector3& operator*=(const TVector3<U>& other);

        /**
         * \brief Divides the current vector by the given one
         * \tparam U The other vector's data type
         * \param other The vector to divide this one by
         * \return A reference to the modified vector
         */
        template <class U>
        TVector3& operator/=(const TVector3<U>& other);

        /**
         * \brief Adds the given value to all of the vector's components
         * \tparam U The value's data type
         * \param value The value to add
         * \return A reference to the modified vector
         */
        template <class U>
        TVector3& operator+=(U value);

        /**
         * \brief Subtracts the given value from all of the vector's components
         * \tparam U The value's data type
         * \param value The value to subtract
         * \return A reference to the modified vector
         */
        template <class U>
        TVector3& operator-=(U value);

        /**
         * \brief Multiplies the current vector by the given scalar
         * \tparam U The scalar's data type
         * \param value The scalar to multiply by
         * \return A reference to the modified vector
         */
        template <class U>
        TVector3& operator*=(U value);

        /**
         * \brief Divides the current vector by the given scalar
         * \tparam U The scalar's data type
         * \param value The scalar to divide by
         * \return A reference to the modified vector
         */
        template <class U>
        TVector3& operator/=(U value);

        /**
         * \brief Gets the vector as an array
         * \return A pointer to the start of the vector
         */
        T* getArray();

        /**
         * \brief Gets the vector as an array
         * \return A pointer to the start of the vector
         */
        const T* getArray() const;

        /**
         * \brief Computes the smallest angle between the given vector and this one
         * \tparam U The other vector's data type
         * \param other The vector from which the angle should be calculated
         * \return The angle between this vector and the other one
         */
        Radian angleFrom(const TVector3& other) const;

        /**
         * \brief Computes the signed angle from the given vector to this one around the given axis
         * \tparam U The other vector's data type
         * \param other The vector from which the angle should be calculated
         * \param axis The axis around which the angle should be calculated
         * \return The signed angle between this vector and the other one
         */
        Radian signedAngleFrom(const TVector3& other, const TVector3& axis) const;

        /**
         * \brief Computes the cross product of this vector and the given one
         * \tparam U The other vector's data type
         * \param other The vector relative to which the cross product should be calculated
         * \return The cross product of the two vectors
         */
        TVector3 cross(const TVector3& other) const;

        /**
         * \brief Computes the distance between this vector and the given one
         * \tparam U The other vector's data type
         * \param other The vector from which the distance should be calculated
         * \return The distance between the two vectors
         */
        T distanceFrom(const TVector3& other) const;

        /**
         * \brief Computes the squared distance between this vector and the given one
         * \tparam U The other vector's data type
         * \param other The vector from which the squared distance should be calculated
         * \return The squared distance between the vectors
         */
        T distanceSquaredFrom(const TVector3& other) const;

        /**
         * \brief Computes the distance between this vector and the given one on the x and y axis only
         * \tparam U The other vector's data type
         * \param other The vector from which the distance should be calculated
         * \return The distance between the two vectors
         */
        T distance2DFrom(const TVector3& other) const;

        /**
         * \brief Computes the squared distance between this vector and the given one on the x and y axis only
         * \tparam U The other vector's data type
         * \param other The vector from which the squared distance should be calculated
         * \return The squared distance between the vectors
         */
        T distance2DSquaredFrom(const TVector3& other) const;

        /**
         * \brief Computes the dot product of the current vector and the other one
         * \tparam U The other vector's data type
         * \param other The vector with which the dot product should be calculated
         * \return The dot product of the two vectors
         */
        template <class U>
        T dot(const TVector3<U>& other) const;

        /**
         * \brief Checks whether this vector's magnitude is greater than the given one's
         * \tparam U The other vector's data type
         * \param other The vector of which magnitude should be compared to this one
         * \return True if this vector's magnitude is greater than the other's. False otherwise
         */
        template <class U>
        bool isLongerThan(const TVector3<U>& other) const;

        /**
         * \brief Checks whether this vector's magnitude is smaller than the given one's
         * \tparam U The other vector's data type
         * \param other The vector of which magnitude should be compared to this one
         * \return True if this vector's magnitude is smaller than the other's. False otherwise
         */
        template <class U>
        bool isShorterThan(const TVector3<U>& other) const;

        /**
         * \brief Checks whether this vector's magnitude is 1
         * \return True if this vector is a unit vector. False otherwise
         */
        bool isUnitVector() const;

        /**
         * \brief Computes this vector's magnitude
         * \return This vector's magnitude
         */
        T magnitude() const;

        /**
         * \brief Computes this vector's squared magnitude
         * \return This vector's squared magnitude
         */
        T magnitudeSquared() const;

        /**
         * \brief Normalizes the vector
         */
        void normalize();

        /**
         * \brief Returns a normalized copy of the vector
         * \return The normalized vector
         */
        TVector3 normalized() const;

        /**
         * \brief Projects this vector on the given normal
         * \param normal The normal to project the vector on
         */
        void projectOnto(const TVector3& normal);

        /**
         * \brief Reflects this vector on the given one
         * \param other The vector relative to which the reflection should occur
         */
        void reflectOnto(const TVector3& other);

        /**
         * \brief Rotates this vector using euler angle apply in the z, x, y order
         * \param xAngle The rotation angle around the x axis
         * \param yAngle The rotation angle around the y axis
         * \param zAngle The rotation angle around the z axis
         */
        void rotate(const Radian& xAngle, const Radian& yAngle, const Radian& zAngle);

        /**
         * \brief Rotates this vector by the given angle around the given axis
         * \param angle The rotation angle
         * \param axis The rotation axis
         */
        void rotate(const Radian& angle, const TVector3& axis);

        /**
         * \brief Rotates this vector using the given quaternion
         * \tparam U The quaternion's data type
         * \param quaternion The quaternion rotor
         */
        template <class U>
        void rotate(const TQuaternion<U>& quaternion);

        /**
         * \brief Scales this vector by the given one
         * \param other The vector to scale this one by
         */
        void scale(const TVector3& other);

        /**
         * \brief Offsets this vector by the given one
         * \param other The vector by which this one should be translate
         */
        void translate(const TVector3& other);

        /**
         * \brief Gets a string representation of this vector
         * \return The string representation of this vector
         */
        std::string string() const;

        /**
         * \brief Gets a verbose string representation of this vector
         * \return The verbose string representation of this vector
         */
        std::string stringLong() const;

        T m_x = static_cast<T>(0);
        T m_y = static_cast<T>(0);
        T m_z = static_cast<T>(0);
    };

    /**
     * \brief Checks whether two vectors' components are equal
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return True if the left and right vectors' components are equal. False otherwise
     */
    template <class T, class U>
    bool operator==(const TVector3<T>& left, const TVector3<U>& right);

    /**
     * \brief Checks whether two vectors' components are different
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return True if the left and right vectors' components are different. False otherwise
     */
    template <class T, class U>
    bool operator!=(const TVector3<T>& left, const TVector3<U>& right);

    /**
     * \brief Checks whether the left vector's magnitude is greater than the right vector's magnitude
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return True if the left vector has a greater magnitude. False otherwise
     */
    template <class T, class U>
    bool operator>(const TVector3<T>& left, const TVector3<U>& right);

    /**
     * \brief Checks whether the left vector's magnitude is smaller than the right vector's magnitude
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return True if the left vector has a smaller magnitude. False otherwise
     */
    template <class T, class U>
    bool operator<(const TVector3<T>& left, const TVector3<U>& right);

    /**
     * \brief Checks whether the left vector's magnitude is greater than or equal to the right vector's magnitude
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return True if the left vector has a greater or equal magnitude. False otherwise
     */
    template <class T, class U>
    bool operator>=(const TVector3<T>& left, const TVector3<U>& right);

    /**
     * \brief Checks whether the left vector's magnitude is smaller than or equal the right vector's magnitude
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return True if the left vector has a smaller or equal magnitude. False otherwise
     */
    template <class T, class U>
    bool operator<=(const TVector3<T>& left, const TVector3<U>& right);

    /**
     * \brief Creates a copy of the given vector with all its components inverted
     * \tparam T The vector's data type
     * \param vector The source vector
     * \return A copy of the vector with all its components inverted
     */
    template <class T>
    TVector3<T> operator-(const TVector3<T>& vector);

    /**
     * \brief Adds the right vector to the left one
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return The sum of the left and right vector
     */
    template <class T, class U>
    TVector3<T> operator+(TVector3<T> left, const TVector3<U>& right);

    /**
     * \brief Subtract the right vector from the left one
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return The difference of the left and right vectors
     */
    template <class T, class U>
    TVector3<T> operator-(TVector3<T> left, const TVector3<U>& right);

    /**
     * \brief Multiplies the left vector by the right one
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return The left vector multiplied by the right vector
     */
    template <class T, class U>
    TVector3<T> operator*(TVector3<T> left, const TVector3<U>& right);

    /**
     * \brief Divides the left vector by the right one
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return The left vector divided by the right vector
     */
    template <class T, class U>
    TVector3<T> operator/(TVector3<T> left, const TVector3<U>& right);

    /**
     * \brief Adds the given value to all of the vector's components
     * \tparam T The vector's data type
     * \tparam U The value's data type
     * \param value The value to add
     * \param vector The vector to add the value to
     * \return The vector with the value added to all its components
     */
    template <class T, class U>
    TVector3<T> operator+(TVector3<T> vector, U value);

    /**
     * \brief Subtracts a value from all of the vector's components
     * \tparam T The vector's data type
     * \tparam U The value's data type
     * \param value The value to subtract
     * \param vector The vector to subtract the value from
     * \return The vector with the value subtracted from all of its components
     */
    template <class T, class U>
    TVector3<T> operator-(TVector3<T> vector, U value);

    /**
     * \brief Multiplies the given vector by a scalar
     * \tparam T The vector's data type
     * \tparam U The scalar's data type
     * \param vector The vector to multiply
     * \param scalar The scalar to multiply by
     * \return The vector multiplied by the scalar
     */
    template <class T, class U>
    TVector3<T> operator*(TVector3<T> vector, U scalar);

    /**
     * \brief Multiplies the given vector by a scalar
     * \tparam T The vector's data type
     * \tparam U The scalar's data type
     * \param scalar The scalar to multiply by
     * \param vector The vector to multiply
     * \return The vector multiplied by the scalar
     */
    template <class T, class U>
    TVector3<U> operator*(U scalar, TVector3<T> vector);

    /**
     * \brief Divides the given vector by a scalar
     * \tparam T The vector's data type
     * \tparam U The scalar's data type
     * \param scalar The scalar to divide by
     * \param vector The vector to divide
     * \return The vector divided by the scalar
     */
    template <class T, class U>
    TVector3<T> operator/(TVector3<T> vector, U scalar);

    /**
     * \brief Adds a vector string representation to an output stream
     * \tparam T The vector's data type
     * \param stream The input stream
     * \param vector The output vector
     * \return The modified stream
     */
    template <class T>
    std::ostream& operator<<(std::ostream& stream, const TVector3<T>& vector);

    /**
     * \brief Parses a string representation from an input stream into a vector
     * \tparam T The vector's data type
     * \param stream The input stream
     * \param vector The output vector
     * \return The modified stream
     */
    template <class T>
    std::istream& operator>>(std::istream& stream, TVector3<T>& vector);

#define VEC3_ALIAS_IMPL(DataType, Alias)                                             \
    using Alias = TVector3<DataType>;                                                \
                                                                                     \
    template <>                                                                      \
    inline Alias clamp<Alias>(const Alias value, const Alias a, const Alias b)       \
    {                                                                                \
        return                                                                       \
        {                                                                            \
            clamp(value.m_x, a.m_x, b.m_x),                                          \
            clamp(value.m_y, a.m_y, b.m_y),                                          \
            clamp(value.m_z, a.m_z, b.m_z)                                           \
        };                                                                           \
    }                                                                                \
                                                                                     \
    template <>                                                                      \
    inline Alias snap<Alias>(const Alias value, const Alias a, const Alias b)        \
    {                                                                                \
        return                                                                       \
        {                                                                            \
            snap(value.m_x, a.m_x, b.m_x),                                           \
            snap(value.m_y, a.m_y, b.m_y),                                           \
            snap(value.m_z, a.m_z, b.m_z)                                            \
        };                                                                           \
    }                                                                                \
                                                                                     \
    template <>                                                                      \
    constexpr bool isInRange<Alias>(const Alias value, const Alias a, const Alias b) \
    {                                                                                \
        return isInRange(value.m_x, a.m_x, b.m_x)                                    \
            && isInRange(value.m_y, a.m_y, b.m_y)                                    \
            && isInRange(value.m_z, a.m_z, b.m_z);                                   \
    }                                                                                \
                                                                                     \
    template <>                                                                      \
    inline Alias min<Alias>(const Alias a, const Alias b)                            \
    {                                                                                \
        return {                                                                     \
            min(a.m_x, b.m_x),                                                       \
            min(a.m_y, b.m_y),                                                       \
            min(a.m_z, b.m_z)                                                        \
        };                                                                           \
    }                                                                                \
                                                                                     \
    template <>                                                                      \
    inline Alias max<Alias>(const Alias a, const Alias b)                            \
    {                                                                                \
        return {                                                                     \
            max(a.m_x, b.m_x),                                                       \
            max(a.m_y, b.m_y),                                                       \
            max(a.m_z, b.m_z)                                                        \
        };                                                                           \
    }

    VEC3_ALIAS_IMPL(float, Vector3F)
    VEC3_ALIAS_IMPL(double, Vector3D)
    VEC3_ALIAS_IMPL(int, Vector3I)
    VEC3_ALIAS_IMPL(long, Vector3L)
    using Vector3 = TVector3<float>;
}

#include "Vector/Vector3.inl"

#endif // !__LIBMATH__VECTOR__VECTOR3_H__
