#ifndef __LIBMATH__VECTOR__VECTOR4_INL__
#define __LIBMATH__VECTOR__VECTOR4_INL__

#include "Quaternion.h"

#include "Angle/Radian.h"

#include "Matrix/Matrix4.h"

#include "Vector/Vector4.h"

namespace LibMath
{
    template <class T>
    TVector4<T> TVector4<T>::zero()
    {
        return { static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0) };
    }

    template <class T>
    TVector4<T> TVector4<T>::one()
    {
        return { static_cast<T>(1), static_cast<T>(1), static_cast<T>(1), static_cast<T>(1) };
    }

    template <class T>
    TVector4<T> TVector4<T>::up()
    {
        return { static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0) };
    }

    template <class T>
    TVector4<T> TVector4<T>::down()
    {
        return { static_cast<T>(0), static_cast<T>(-1), static_cast<T>(0), static_cast<T>(0) };
    }

    template <class T>
    TVector4<T> TVector4<T>::left()
    {
        return { static_cast<T>(-1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0) };
    }

    template <class T>
    TVector4<T> TVector4<T>::right()
    {
        return { static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0) };
    }

    template <class T>
    TVector4<T> TVector4<T>::front()
    {
        return { static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0) };
    }

    template <class T>
    TVector4<T> TVector4<T>::back()
    {
        return { static_cast<T>(0), static_cast<T>(0), static_cast<T>(-1), static_cast<T>(0) };
    }

    template <class T>
    TVector4<T>::TVector4(const T value)
        : TVector4(value, value, value, value)
    {
    }

    template <class T>
    TVector4<T>::TVector4(const T x, const T y, const T z, const T w)
        : m_x(x), m_y(y), m_z(z), m_w(w)
    {
    }

    template <class T>
    template <class U, class W>
    TVector4<T>::TVector4(const TVector3<U>& other, const W w)
        : m_x(static_cast<T>(other.m_x)), m_y(static_cast<T>(other.m_y)), m_z(static_cast<T>(other.m_z)), m_w(static_cast<T>(w))
    {
        static_assert(std::is_arithmetic_v<W>, "Invalid value - Data type should be an arithmetic type");
    }

    template <class T>
    template <class U>
    TVector4<T>::TVector4(const TVector4<U>& other)
        : TVector4(static_cast<T>(other.m_x), static_cast<T>(other.m_y), static_cast<T>(other.m_z), static_cast<T>(other.m_w))
    {
    }

    template <class T>
    template <class U>
    TVector4<T>::TVector4(TVector4<U>&& other)
        : TVector4(static_cast<T>(other.m_x), static_cast<T>(other.m_y), static_cast<T>(other.m_z), static_cast<T>(other.m_w))
    {
    }

    template <class T>
    template <class U>
    TVector4<T>& TVector4<T>::operator=(const TVector4<U>& other)
    {
        if (reinterpret_cast<const TVector4*>(&other) == this)
            return *this;

        m_x = static_cast<T>(other.m_x);
        m_y = static_cast<T>(other.m_y);
        m_z = static_cast<T>(other.m_z);
        m_w = static_cast<T>(other.m_w);

        return *this;
    }

    template <class T>
    template <class U>
    TVector4<T>& TVector4<T>::operator=(TVector4<U>&& other)
    {
        if (reinterpret_cast<const TVector4*>(&other) == this)
            return *this;

        m_x = static_cast<T>(other.m_x);
        m_y = static_cast<T>(other.m_y);
        m_z = static_cast<T>(other.m_z);
        m_w = static_cast<T>(other.m_w);

        return *this;
    }

    template <class T>
    T& TVector4<T>::operator[](const int index)
    {
        switch (index)
        {
        case 0:
        case 'x':
        case 'X':
            return this->m_x;
        case 1:
        case 'y':
        case 'Y':
            return this->m_y;
        case 2:
        case 'z':
        case 'Z':
            return this->m_z;
        case 3:
        case 'w':
        case 'W':
            return this->m_w;
        default:
            throw std::out_of_range("Invalid index \"" + std::to_string(index) + "\" received");
        }
    }

    template <class T>
    T TVector4<T>::operator[](const int index) const
    {
        switch (index)
        {
        case 0:
            return this->m_x;
        case 1:
            return this->m_y;
        case 2:
            return this->m_z;
        case 3:
            return this->m_w;
        default:
            throw std::out_of_range("Invalid index \"" + std::to_string(index) + "\" received");
        }
    }

    template <class T>
    template <class U>
    TVector4<T>& TVector4<T>::operator+=(const TVector4<U>& other)
    {
        this->m_x += static_cast<T>(other.m_x);
        this->m_y += static_cast<T>(other.m_y);
        this->m_z += static_cast<T>(other.m_z);
        this->m_w += static_cast<T>(other.m_w);

        return *this;
    }

    template <class T>
    template <class U>
    TVector4<T>& TVector4<T>::operator-=(const TVector4<U>& other)
    {
        this->m_x -= static_cast<T>(other.m_x);
        this->m_y -= static_cast<T>(other.m_y);
        this->m_z -= static_cast<T>(other.m_z);
        this->m_w -= static_cast<T>(other.m_w);

        return *this;
    }

    template <class T>
    template <class U>
    TVector4<T>& TVector4<T>::operator*=(const TVector4<U>& other)
    {
        this->m_x = static_cast<T>(this->m_x * other.m_x);
        this->m_y = static_cast<T>(this->m_y * other.m_y);
        this->m_z = static_cast<T>(this->m_z * other.m_z);
        this->m_w = static_cast<T>(this->m_w * other.m_w);

        return *this;
    }

    template <class T>
    template <class U>
    TVector4<T>& TVector4<T>::operator/=(const TVector4<U>& other)
    {
        this->m_x = static_cast<T>(this->m_x / other.m_x);
        this->m_y = static_cast<T>(this->m_y / other.m_y);
        this->m_z = static_cast<T>(this->m_z / other.m_z);
        this->m_w = static_cast<T>(this->m_w / other.m_w);

        return *this;
    }

    template <class T>
    template <class U>
    TVector4<T>& TVector4<T>::operator+=(U value)
    {
        static_assert(std::is_arithmetic_v<U>, "Invalid value - Data type should be an arithmetic type");

        this->m_x += static_cast<T>(value);
        this->m_y += static_cast<T>(value);
        this->m_z += static_cast<T>(value);
        this->m_w += static_cast<T>(value);

        return *this;
    }

    template <class T>
    template <class U>
    TVector4<T>& TVector4<T>::operator-=(U value)
    {
        static_assert(std::is_arithmetic_v<U>, "Invalid value - Data type should be an arithmetic type");

        this->m_x -= static_cast<T>(value);
        this->m_y -= static_cast<T>(value);
        this->m_z -= static_cast<T>(value);
        this->m_w -= static_cast<T>(value);

        return *this;
    }

    template <class T>
    template <class U>
    TVector4<T>& TVector4<T>::operator*=(U value)
    {
        static_assert(std::is_arithmetic_v<U>, "Invalid value - Data type should be an arithmetic type");

        this->m_x = static_cast<T>(this->m_x * value);
        this->m_y = static_cast<T>(this->m_y * value);
        this->m_z = static_cast<T>(this->m_z * value);
        this->m_w = static_cast<T>(this->m_w * value);

        return *this;
    }

    template <class T>
    template <class U>
    TVector4<T>& TVector4<T>::operator/=(U value)
    {
        static_assert(std::is_arithmetic_v<U>, "Invalid value - Data type should be an arithmetic type");

        this->m_x = static_cast<T>(this->m_x / value);
        this->m_y = static_cast<T>(this->m_y / value);
        this->m_z = static_cast<T>(this->m_z / value);
        this->m_w = static_cast<T>(this->m_w / value);

        return *this;
    }

    template <class T>
    T* TVector4<T>::getArray()
    {
        return &m_x;
    }

    template <class T>
    const T* TVector4<T>::getArray() const
    {
        return &m_x;
    }

    template <class T>
    TVector3<T> TVector4<T>::xyz() const
    {
        return { this->m_x, this->m_y, this->m_z };
    }

    template <class T>
    template <class U>
    T TVector4<T>::distanceFrom(const TVector4<U>& other) const
    {
        return squareRoot(distanceSquaredFrom(other));
    }

    template <class T>
    template <class U>
    T TVector4<T>::distanceSquaredFrom(const TVector4<U>& other) const
    {
        const T xDist = other.m_x - this->m_x;
        const T yDist = other.m_y - this->m_y;
        const T zDist = other.m_z - this->m_z;
        const T wDist = other.m_w - this->m_w;

        return xDist * xDist + yDist * yDist + zDist * zDist + wDist * wDist;
    }

    template <class T>
    template <class U>
    T TVector4<T>::dot(const TVector4<U>& other) const
    {
        return static_cast<T>(this->m_x * other.m_x +
            this->m_y * other.m_y +
            this->m_z * other.m_z +
            this->m_w * other.m_w);
    }

    template <class T>
    template <class U>
    bool TVector4<T>::isLongerThan(const TVector4<U>& other) const
    {
        return this->magnitudeSquared() > static_cast<T>(other.magnitudeSquared());
    }

    template <class T>
    template <class U>
    bool TVector4<T>::isShorterThan(const TVector4<U>& other) const
    {
        return this->magnitudeSquared() < static_cast<T>(other.magnitudeSquared());
    }

    template <class T>
    bool TVector4<T>::isUnitVector() const
    {
        return floatEquals<T>(1, this->magnitudeSquared());
    }

    template <class T>
    T TVector4<T>::magnitude() const
    {
        return squareRoot(this->magnitudeSquared());
    }

    template <class T>
    T TVector4<T>::magnitudeSquared() const
    {
        return this->m_x * this->m_x +
            this->m_y * this->m_y +
            this->m_z * this->m_z +
            this->m_w * this->m_w;
    }

    template <class T>
    void TVector4<T>::normalize()
    {
        *this /= this->magnitude();
    }

    template <class T>
    TVector4<T> TVector4<T>::normalized() const
    {
        return *this / this->magnitude();
    }

    template <class T>
    void TVector4<T>::rotate(const Radian& xAngle, const Radian& yAngle, const Radian& zAngle)
    {
        const TMatrix<4, 4, T> rotationMat = rotationEuler<T>(xAngle, yAngle, zAngle);
        *this = rotationMat * *this;
    }

    template <class T>
    void TVector4<T>::rotate(const Radian& angle, const TVector3<T>& axis)
    {
        const TMatrix<4, 4, T> rotationMat = rotation<T>(angle, axis);
        *this = rotationMat * *this;
    }

    template <class T>
    template <class U>
    void TVector4<T>::rotate(const TQuaternion<U>& quaternion)
    {
        TQuaternion<U> tmp{ m_w, this->xyz() };
        *this = quaternion * tmp * quaternion.inverse();
    }

    template <class T>
    void TVector4<T>::scale(const TVector3<T>& other)
    {
        *this *= other;
    }

    template <class T>
    void TVector4<T>::translate(const TVector3<T>& other)
    {
        *this += other;
    }

    template <class T>
    std::string TVector4<T>::string() const
    {
        std::ostringstream oss;

        oss << "{" << this->m_x << "," << this->m_y
            << "," << this->m_z << "," << this->m_w << "}";

        return oss.str();
    }

    template <class T>
    std::string TVector4<T>::stringLong() const
    {
        std::ostringstream oss;

        oss << "TVector4{ x:" << this->m_x << ", y:" << this->m_y
            << ", z:" << this->m_z << ", w:" << this->m_w << " }";

        return oss.str();
    }

    template <class T, class U>
    bool operator==(const TVector4<T>& left, const TVector4<U>& right)
    {
        return floatEquals(left.m_x, static_cast<T>(right.m_x)) &&
            floatEquals(left.m_y, static_cast<T>(right.m_y)) &&
            floatEquals(left.m_z, static_cast<T>(right.m_z)) &&
            floatEquals(left.m_w, static_cast<T>(right.m_w));
    }

    template <class T, class U>
    bool operator!=(const TVector4<T>& left, const TVector4<U>& right)
    {
        return !(left == right);
    }

    template <class T, class U>
    bool operator>(const TVector4<T>& left, const TVector4<U>& right)
    {
        return left.isLongerThan(right);
    }

    template <class T, class U>
    bool operator<(const TVector4<T>& left, const TVector4<U>& right)
    {
        return right > left;
    }

    template <class T, class U>
    bool operator>=(const TVector4<T>& left, const TVector4<U>& right)
    {
        return !(left < right);
    }

    template <class T, class U>
    bool operator<=(const TVector4<T>& left, const TVector4<U>& right)
    {
        return !(left > right);
    }

    template <class T>
    TVector4<T> operator-(const TVector4<T>& vector)
    {
        return { -vector.m_x, -vector.m_y, -vector.m_z, -vector.m_w };
    }

    template <class T, class U>
    TVector4<T> operator+(TVector4<T> left, const TVector4<U>& right)
    {
        return left += right;
    }

    template <class T, class U>
    TVector4<T> operator-(TVector4<T> left, const TVector4<U>& right)
    {
        return left -= right;
    }

    template <class T, class U>
    TVector4<T> operator*(TVector4<T> left, const TVector4<U>& right)
    {
        return left *= right;
    }

    template <class T, class U>
    TVector4<T> operator/(TVector4<T> left, const TVector4<U>& right)
    {
        return left /= right;
    }

    template <class T, class U>
    TVector4<T> operator+(TVector4<T> vector, U value)
    {
        return vector += value;
    }

    template <class T, class U>
    TVector4<T> operator-(TVector4<T> vector, U value)
    {
        return vector -= value;
    }

    template <class T, class U>
    TVector4<T> operator*(TVector4<T> vector, U scalar)
    {
        return vector *= scalar;
    }

    template <class T, class U>
    TVector4<U> operator*(U scalar, TVector4<T> vector)
    {
        return vector *= scalar;
    }

    template <class T, class U>
    TVector4<T> operator/(TVector4<T> vector, U scalar)
    {
        return vector /= scalar;
    }

    template <class T>
    std::ostream& operator<<(std::ostream& stream, const TVector4<T>& vector)
    {
        return stream << vector.string();
    }

    template <class T>
    std::istream& operator>>(std::istream& stream, TVector4<T>& vector)
    {
        std::string line;

        std::getline(stream, line, '}');

        int    component = 0;
        size_t valStart = 0;

        do
        {
            if (valStart == std::string::npos)
                break;

            if (line[valStart] == '{' || std::isspace(line[valStart]))
            {
                valStart++;
                continue;
            }

            if (line[valStart] != '-' && !std::isdigit(line[valStart]))
                break;

            vector[component] = std::stof(line.substr(valStart));

            valStart = line.find(',', valStart) + 1;
            component++;
        }
        while (component < 4 && valStart != 0);

        if (component != 4)
            vector = TVector4<T>::zero();

        return stream;
    }
}

#endif // !__LIBMATH__VECTOR__VECTOR4_INL__
