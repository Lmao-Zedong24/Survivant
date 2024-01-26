#ifndef __LIBMATH__VECTOR__VECTOR2_H__
#define __LIBMATH__VECTOR__VECTOR2_H__

#include <string>

#include "Arithmetic.h"

#include "Angle/Radian.h"

#include "Vector/Vector3.h"

namespace LibMath
{
    template <class T>
    class TVector2
    {
        static_assert(std::is_arithmetic_v<T>, "Invalid vector - Data type should be an arithmetic type");

    public:
        /**
         * \brief Returns a vector with all its components set to 0
         */
        static TVector2 zero();

        /**
         * \brief Returns a vector with all its components set to 1
         */
        static TVector2 one();

        /**
         * \brief Returns a vector pointing upward
         */
        static TVector2 up();

        /**
         * \brief Returns a vector pointing downward
         */
        static TVector2 down();

        /**
         * \brief Returns a vector pointing left
         */
        static TVector2 left();

        /**
         * \brief Returns a vector pointing right
         */
        static TVector2 right();

        /**
         * \brief Creates a default vector
         */
        TVector2() = default;

        /**
         * \brief Creates a vector with the given value for all its components
         * \param value The vector's components value
         */
        explicit TVector2(T value);

        /**
         * \brief Creates a vector with the given component values
         * \param x The vector's x value
         * \param y The vector's y value
         */
        TVector2(T x, T y);

        /**
         * \brief Creates a copy of the given vector
         * \tparam U The copied vector's data type
         * \param other The copied vector
         */
        template <class U>
        TVector2(const TVector2<U>& other);

        /**
         * \brief Creates a move copy of the given vector
         * \tparam U The moved vector's data type
         * \param other The moved vector
         */
        template <class U>
        TVector2(TVector2<U>&& other) noexcept;

        /**
         * \brief Destroys the vector
         */
        ~TVector2() = default;

        /**
         * \brief Converts the TVector2 to a TVcetor3
         */
        operator TVector3<T>() const;

        /**
         * \brief Assigns a copy of the given vector to the current one
         * \tparam U The copied vector's data type
         * \param other The copied vector
         * \return The modified vector
         */
        template <class U>
        TVector2& operator=(const TVector2<U>& other);

        /**
         * \brief Assigns a move copy of the given vector to the current one
         * \tparam U The moved vector's data type
         * \param other The moved vector
         * \return The modified vector
         */
        template <class U>
        TVector2& operator=(TVector2<U>&& other) noexcept;

        /**
         * \brief Gets the vector's component at the given index (0/'x', 1/'y')
         * \param index The component's index
         * \return The component at the given index
         */
        T& operator[](int index);

        /**
         * \brief Gets the vector's component at the given index (0/'x', 1/'y')
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
        TVector2& operator+=(const TVector2<U>& other);

        /**
         * \brief Subtracts the given vector from the current one
         * \tparam U The other vector's data type
         * \param other The vector to subtract from this one
         * \return A reference to the modified vector
         */
        template <class U>
        TVector2& operator-=(const TVector2<U>& other);

        /**
         * \brief Multiplies the current vector by the given one
         * \tparam U The other vector's data type
         * \param other The vector to multiply this one by
         * \return A reference to the modified vector
         */
        template <class U>
        TVector2& operator*=(const TVector2<U>& other);

        /**
         * \brief Divides the current vector by the given one
         * \tparam U The other vector's data type
         * \param other The vector to divide this one by
         * \return A reference to the modified vector
         */
        template <class U>
        TVector2& operator/=(const TVector2<U>& other);

        /**
         * \brief Adds the given value to all of the vector's components
         * \tparam U The value's data type
         * \param value The value to add
         * \return A reference to the modified vector
         */
        template <class U>
        TVector2& operator+=(U value);

        /**
         * \brief Subtracts the given value from all of the vector's components
         * \tparam U The value's data type
         * \param value The value to subtract
         * \return A reference to the modified vector
         */
        template <class U>
        TVector2& operator-=(U value);

        /**
         * \brief Multiplies the current vector by the given scalar
         * \tparam U The scalar's data type
         * \param value The scalar to multiply by
         * \return A reference to the modified vector
         */
        template <class U>
        TVector2& operator*=(U value);

        /**
         * \brief Divides the current vector by the given scalar
         * \tparam U The scalar's data type
         * \param value The scalar to divide by
         * \return A reference to the modified vector
         */
        template <class U>
        TVector2& operator/=(U value);

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
        template <class U>
        Radian angleFrom(const TVector2<U>& other) const;

        /**
         * \brief Computes the signed angle from the given vector to this one
         * \tparam U The other vector's data type
         * \param other The vector from which the angle should be calculated
         * \return The signed angle between this vector and the other one
         */
        template <class U>
        Radian signedAngleFrom(const TVector2<U>& other) const;

        /**
         * \brief Computes the cross product of this vector and the given one
         * \tparam U The other vector's data type
         * \param other The vector relative to which the cross product should be calculated
         * \return The cross product of the two vectors
         */
        template <class U>
        T cross(const TVector2<U>& other) const;

        /**
         * \brief Computes the distance between this vector and the given one
         * \tparam U The other vector's data type
         * \param other The vector from which the distance should be calculated
         * \return The distance between the two vectors
         */
        template <class U>
        T distanceFrom(const TVector2<U>& other) const;

        /**
         * \brief Computes the squared distance between this vector and the given one
         * \tparam U The other vector's data type
         * \param other The vector from which the squared distance should be calculated
         * \return The squared distance between the vectors
         */
        template <class U>
        T distanceSquaredFrom(const TVector2<U>& other) const;

        /**
         * \brief Computes the dot product of the current vector and the other one
         * \tparam U The other vector's data type
         * \param other The vector with which the dot product should be calculated
         * \return The dot product of the two vectors
         */
        template <class U>
        T dot(const TVector2<U>& other) const;

        /**
         * \brief Checks whether this vector's magnitude is greater than the given one's
         * \tparam U The other vector's data type
         * \param other The vector of which magnitude should be compared to this one
         * \return True if this vector's magnitude is greater than the other's. False otherwise
         */
        template <class U>
        bool isLongerThan(const TVector2<U>& other) const;

        /**
         * \brief Checks whether this vector's magnitude is smaller than the given one's
         * \tparam U The other vector's data type
         * \param other The vector of which magnitude should be compared to this one
         * \return True if this vector's magnitude is smaller than the other's. False otherwise
         */
        template <class U>
        bool isShorterThan(const TVector2<U>& other) const;

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
        TVector2 normalized() const;

        /**
         * \brief Projects this vector on the given normal
         * \param normal The normal to project the vector on
         */
        void projectOnto(const TVector2& normal);

        /**
         * \brief Reflects this vector on the given one
         * \param other The vector relative to which the reflection should occur
         */
        void reflectOnto(const TVector2& other);

        /**
         * \brief Rotates this vector by the given angle
         * \param angle The rotation angle
         */
        void rotate(const Radian& angle);

        /**
         * \brief Scales this vector by the given one
         * \param other The vector to scale this one by
         */
        void scale(const TVector2& other);

        /**
         * \brief Offsets this vector by the given one
         * \param other The vector by which this one should be translate
         */
        void translate(const TVector2& other);

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

        T m_x = 0;
        T m_y = 0;
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
    bool operator==(const TVector2<T>& left, const TVector2<U>& right);

    /**
     * \brief Checks whether two vectors' components are different
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return True if the left and right vectors' components are different. False otherwise
     */
    template <class T, class U>
    bool operator!=(const TVector2<T>& left, const TVector2<U>& right);

    /**
     * \brief Checks whether the left vector's magnitude is greater than the right vector's magnitude
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return True if the left vector has a greater magnitude. False otherwise
     */
    template <class T, class U>
    bool operator>(const TVector2<T>& left, const TVector2<U>& right);

    /**
     * \brief Checks whether the left vector's magnitude is smaller than the right vector's magnitude
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return True if the left vector has a smaller magnitude. False otherwise
     */
    template <class T, class U>
    bool operator<(const TVector2<T>& left, const TVector2<U>& right);

    /**
     * \brief Checks whether the left vector's magnitude is greater than or equal to the right vector's magnitude
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return True if the left vector has a greater or equal magnitude. False otherwise
     */
    template <class T, class U>
    bool operator>=(const TVector2<T>& left, const TVector2<U>& right);

    /**
     * \brief Checks whether the left vector's magnitude is smaller than or equal the right vector's magnitude
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return True if the left vector has a smaller or equal magnitude. False otherwise
     */
    template <class T, class U>
    bool operator<=(const TVector2<T>& left, const TVector2<U>& right);

    /**
     * \brief Creates a copy of the given vector with all its components inverted
     * \tparam T The vector's data type
     * \param vector The source vector
     * \return A copy of the vector with all its components inverted
     */
    template <class T>
    TVector2<T> operator-(const TVector2<T>& vector);

    /**
     * \brief Adds the right vector to the left one
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return The sum of the left and right vector
     */
    template <class T, class U>
    TVector2<T> operator+(TVector2<T> left, const TVector2<U>& right);

    /**
     * \brief Subtract the right vector from the left one
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return The difference of the left and right vectors
     */
    template <class T, class U>
    TVector2<T> operator-(TVector2<T> left, const TVector2<U>& right);

    /**
     * \brief Multiplies the left vector by the right one
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return The left vector multiplied by the right vector
     */
    template <class T, class U>
    TVector2<T> operator*(TVector2<T> left, const TVector2<U>& right);

    /**
     * \brief Divides the left vector by the right one
     * \tparam T The left vector's data type
     * \tparam U The right vector's data type
     * \param left The left vector
     * \param right The right vector
     * \return The left vector divided by the right vector
     */
    template <class T, class U>
    TVector2<T> operator/(TVector2<T> left, const TVector2<U>& right);

    /**
     * \brief Adds the given value to all of the vector's components
     * \tparam T The vector's data type
     * \tparam U The value's data type
     * \param value The value to add
     * \param vector The vector to add the value to
     * \return The vector with the value added to all its components
     */
    template <class T, class U>
    TVector2<T> operator+(TVector2<T> vector, U value);

    /**
     * \brief Subtracts a value from all of the vector's components
     * \tparam T The vector's data type
     * \tparam U The value's data type
     * \param value The value to subtract
     * \param vector The vector to subtract the value from
     * \return The vector with the value subtracted from all of its components
     */
    template <class T, class U>
    TVector2<T> operator-(TVector2<T> vector, U value);

    /**
     * \brief Multiplies the given vector by a scalar
     * \tparam T The vector's data type
     * \tparam U The scalar's data type
     * \param vector The vector to multiply
     * \param scalar The scalar to multiply by
     * \return The vector multiplied by the scalar
     */
    template <class T, class U>
    TVector2<T> operator*(TVector2<T> vector, U scalar);

    /**
     * \brief Multiplies the given vector by a scalar
     * \tparam T The vector's data type
     * \tparam U The scalar's data type
     * \param scalar The scalar to multiply by
     * \param vector The vector to multiply
     * \return The vector multiplied by the scalar
     */
    template <class T, class U>
    TVector2<U> operator*(U scalar, TVector2<T> vector);

    /**
     * \brief Divides the given vector by a scalar
     * \tparam T The vector's data type
     * \tparam U The scalar's data type
     * \param scalar The scalar to divide by
     * \param vector The vector to divide
     * \return The vector divided by the scalar
     */
    template <class T, class U>
    TVector2<T> operator/(TVector2<T> vector, U scalar);

    /**
     * \brief Adds a vector string representation to an output stream
     * \tparam T The vector's data type
     * \param stream The input stream
     * \param vector The output vector
     * \return The modified stream
     */
    template <class T>
    std::ostream& operator<<(std::ostream& stream, const TVector2<T>& vector);

    /**
     * \brief Parses a string representation from an input stream into a vector
     * \tparam T The vector's data type
     * \param stream The input stream
     * \param vector The output vector
     * \return The modified stream
     */
    template <class T>
    std::istream& operator>>(std::istream& stream, TVector2<T>& vector);

#define VEC2_ALIAS_IMPL(DataType, Alias)                                             \
    using Alias = TVector2<DataType>;                                                \
                                                                                     \
    template <>                                                                      \
    inline Alias clamp<Alias>(const Alias value, const Alias a, const Alias b)       \
    {                                                                                \
        return                                                                       \
        {                                                                            \
            clamp(value.m_x, a.m_x, b.m_x),                                          \
            clamp(value.m_y, a.m_y, b.m_y)                                           \
        };                                                                           \
    }                                                                                \
                                                                                     \
    template <>                                                                      \
    inline Alias snap<Alias>(const Alias value, const Alias a, const Alias b)        \
    {                                                                                \
        return                                                                       \
        {                                                                            \
            snap(value.m_x, a.m_x, b.m_x),                                           \
            snap(value.m_y, a.m_y, b.m_y)                                            \
        };                                                                           \
    }                                                                                \
                                                                                     \
    template <>                                                                      \
    constexpr bool isInRange<Alias>(const Alias value, const Alias a, const Alias b) \
    {                                                                                \
        return isInRange(value.m_x, a.m_x, b.m_x)                                    \
            && isInRange(value.m_y, a.m_y, b.m_y);                                   \
    }                                                                                \
                                                                                     \
    template <>                                                                      \
    inline Alias min<Alias>(const Alias a, const Alias b)                            \
    {                                                                                \
        return {                                                                     \
            min(a.m_x, b.m_x),                                                       \
            min(a.m_y, b.m_y)                                                        \
        };                                                                           \
    }

    VEC2_ALIAS_IMPL(float, Vector2F)
    VEC2_ALIAS_IMPL(double, Vector2D)
    VEC2_ALIAS_IMPL(int, Vector2I)
    VEC2_ALIAS_IMPL(long, Vector2L)
    using Vector2 = TVector2<float>;
}

#include "Vector/Vector2.inl"

#endif // !__LIBMATH__VECTOR__VECTOR2_H__
