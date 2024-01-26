#ifndef __LIBMATH__VECTOR__VECTOR3_INL__
#define __LIBMATH__VECTOR__VECTOR3_INL__

#include <sstream>

#include "Quaternion.h"

#include "Vector/Vector3.h"
#include "Vector/Vector4.h"

namespace LibMath
{
    template <class T>
    TVector3<T> TVector3<T>::zero()
    {
        return TVector3(0);
    }

    template <class T>
    TVector3<T> TVector3<T>::one()
    {
        return TVector3(1);
    }

    template <class T>
    TVector3<T> TVector3<T>::up()
    {
        return { static_cast<T>(0), static_cast<T>(1), static_cast<T>(0) };
    }

    template <class T>
    TVector3<T> TVector3<T>::down()
    {
        return { static_cast<T>(0), static_cast<T>(-1), static_cast<T>(0) };
    }

    template <class T>
    TVector3<T> TVector3<T>::left()
    {
        return { static_cast<T>(-1), static_cast<T>(0), static_cast<T>(0) };
    }

    template <class T>
    TVector3<T> TVector3<T>::right()
    {
        return { static_cast<T>(1), static_cast<T>(0), static_cast<T>(0) };
    }

    template <class T>
    TVector3<T> TVector3<T>::front()
    {
        return { static_cast<T>(0), static_cast<T>(0), static_cast<T>(1) };
    }

    template <class T>
    TVector3<T> TVector3<T>::back()
    {
        return { static_cast<T>(0), static_cast<T>(0), static_cast<T>(-1) };
    }

    template <class T>
    TVector3<T>::TVector3(const T value)
        : TVector3(value, value, value)
    {
    }

    template <class T>
    TVector3<T>::TVector3(const T x, const T y, const T z)
        : m_x(x), m_y(y), m_z(z)
    {
    }

    template <class T>
    template <class U>
    TVector3<T>::TVector3(const TVector3<U>& other)
        : TVector3(static_cast<T>(other.m_x), static_cast<T>(other.m_y), static_cast<T>(other.m_z))
    {
    }

    template <class T>
    template <class U>
    TVector3<T>::TVector3(TVector3<U>&& other)
        : TVector3(static_cast<T>(other.m_x), static_cast<T>(other.m_y), static_cast<T>(other.m_z))
    {
    }

    template <class T>
    template <class U>
    TVector3<T>& TVector3<T>::operator=(const TVector3<U>& other)
    {
        if (reinterpret_cast<const TVector3*>(&other) == this)
            return *this;

        m_x = static_cast<T>(other.m_x);
        m_y = static_cast<T>(other.m_y);
        m_z = static_cast<T>(other.m_z);

        return *this;
    }

    template <class T>
    template <class U>
    TVector3<T>& TVector3<T>::operator=(TVector3<U>&& other)
    {
        if (reinterpret_cast<const TVector3*>(&other) == this)
            return *this;

        m_x = static_cast<T>(other.m_x);
        m_y = static_cast<T>(other.m_y);
        m_z = static_cast<T>(other.m_z);

        return *this;
    }

    template <class T>
    T& TVector3<T>::operator[](const int index)
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
        default:
            throw std::out_of_range("Invalid index \"" + std::to_string(index) + "\" received");
        }
    }

    template <class T>
    T TVector3<T>::operator[](const int index) const
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
        default:
            throw std::out_of_range("Invalid index \"" + std::to_string(index) + "\" received");
        }
    }

    template <class T>
    template <class U>
    TVector3<T>& TVector3<T>::operator+=(const TVector3<U>& other)
    {
        this->m_x += static_cast<T>(other.m_x);
        this->m_y += static_cast<T>(other.m_y);
        this->m_z += static_cast<T>(other.m_z);

        return *this;
    }

    template <class T>
    template <class U>
    TVector3<T>& TVector3<T>::operator-=(const TVector3<U>& other)
    {
        this->m_x -= static_cast<T>(other.m_x);
        this->m_y -= static_cast<T>(other.m_y);
        this->m_z -= static_cast<T>(other.m_z);

        return *this;
    }

    template <class T>
    template <class U>
    TVector3<T>& TVector3<T>::operator*=(const TVector3<U>& other)
    {
        this->m_x = static_cast<T>(this->m_x * other.m_x);
        this->m_y = static_cast<T>(this->m_y * other.m_y);
        this->m_z = static_cast<T>(this->m_z * other.m_z);

        return *this;
    }

    template <class T>
    template <class U>
    TVector3<T>& TVector3<T>::operator/=(const TVector3<U>& other)
    {
        this->m_x = static_cast<T>(this->m_x / other.m_x);
        this->m_y = static_cast<T>(this->m_y / other.m_y);
        this->m_z = static_cast<T>(this->m_z / other.m_z);

        return *this;
    }

    template <class T>
    template <class U>
    TVector3<T>& TVector3<T>::operator+=(U value)
    {
        static_assert(std::is_arithmetic_v<U>, "Invalid value - Data type should be an arithmetic type");

        this->m_x += static_cast<T>(value);
        this->m_y += static_cast<T>(value);
        this->m_z += static_cast<T>(value);

        return *this;
    }

    template <class T>
    template <class U>
    TVector3<T>& TVector3<T>::operator-=(U value)
    {
        static_assert(std::is_arithmetic_v<U>, "Invalid value - Data type should be an arithmetic type");

        this->m_x -= static_cast<T>(value);
        this->m_y -= static_cast<T>(value);
        this->m_z -= static_cast<T>(value);

        return *this;
    }

    template <class T>
    template <class U>
    TVector3<T>& TVector3<T>::operator*=(U value)
    {
        static_assert(std::is_arithmetic_v<U>, "Invalid value - Data type should be an arithmetic type");

        this->m_x = static_cast<T>(this->m_x * value);
        this->m_y = static_cast<T>(this->m_y * value);
        this->m_z = static_cast<T>(this->m_z * value);

        return *this;
    }

    template <class T>
    template <class U>
    TVector3<T>& TVector3<T>::operator/=(U value)
    {
        static_assert(std::is_arithmetic_v<U>, "Invalid value - Data type should be an arithmetic type");

        this->m_x = static_cast<T>(this->m_x / value);
        this->m_y = static_cast<T>(this->m_y / value);
        this->m_z = static_cast<T>(this->m_z / value);

        return *this;
    }

    template <class T>
    T* TVector3<T>::getArray()
    {
        return &m_x;
    }

    template <class T>
    const T* TVector3<T>::getArray() const
    {
        return &m_x;
    }

    template <class T>
    Radian TVector3<T>::angleFrom(const TVector3& other) const
    {
        return acos(this->dot(other) / squareRoot(this->magnitudeSquared() * other.magnitudeSquared()));
    }

    template <class T>
    Radian TVector3<T>::signedAngleFrom(const TVector3& other, const TVector3& axis) const
    {
        const Radian   angle = angleFrom(other);
        const TVector3 cross = other.cross(*this);
        return angle * sign(axis.m_x * cross.m_x + axis.m_y * cross.m_y + axis.m_z * cross.m_z);
    }

    template <class T>
    TVector3<T> TVector3<T>::cross(const TVector3& other) const
    {
        return {
            this->m_y * other.m_z - this->m_z * other.m_y,
            this->m_z * other.m_x - this->m_x * other.m_z,
            this->m_x * other.m_y - this->m_y * other.m_x
        };
    }

    template <class T>
    T TVector3<T>::distanceFrom(const TVector3& other) const
    {
        return squareRoot(this->distanceSquaredFrom(other));
    }

    template <class T>
    T TVector3<T>::distanceSquaredFrom(const TVector3& other) const
    {
        const T xDist = other.m_x - this->m_x;
        const T yDist = other.m_y - this->m_y;
        const T zDist = other.m_z - this->m_z;

        return xDist * xDist + yDist * yDist + zDist * zDist;
    }

    template <class T>
    T TVector3<T>::distance2DFrom(const TVector3& other) const
    {
        return squareRoot(this->distance2DSquaredFrom(other));
    }

    template <class T>
    T TVector3<T>::distance2DSquaredFrom(const TVector3& other) const
    {
        const T xDist = other.m_x - this->m_x;
        const T yDist = other.m_y - this->m_y;

        return xDist * xDist + yDist * yDist;
    }

    template <class T>
    template <class U>
    T TVector3<T>::dot(const TVector3<U>& other) const
    {
        return static_cast<T>(this->m_x * other.m_x + this->m_y * other.m_y + this->m_z * other.m_z);
    }

    template <class T>
    template <class U>
    bool TVector3<T>::isLongerThan(const TVector3<U>& other) const
    {
        return this->magnitudeSquared() > static_cast<T>(other.magnitudeSquared());
    }

    template <class T>
    template <class U>
    bool TVector3<T>::isShorterThan(const TVector3<U>& other) const
    {
        return this->magnitudeSquared() < static_cast<T>(other.magnitudeSquared());
    }

    template <class T>
    bool TVector3<T>::isUnitVector() const
    {
        return floatEquals<T>(1, this->magnitudeSquared());
    }

    template <class T>
    T TVector3<T>::magnitude() const
    {
        return squareRoot(this->magnitudeSquared());
    }

    template <class T>
    T TVector3<T>::magnitudeSquared() const
    {
        return this->m_x * this->m_x + this->m_y * this->m_y + this->m_z * this->m_z;
    }

    template <class T>
    void TVector3<T>::normalize()
    {
        *this /= this->magnitude();
    }

    template <class T>
    TVector3<T> TVector3<T>::normalized() const
    {
        return *this / this->magnitude();
    }

    template <class T>
    void TVector3<T>::projectOnto(const TVector3& normal)
    {
        *this = this->dot(normal) / normal.magnitudeSquared() * normal;
    }

    // Adapted from https://math.stackexchange.com/a/4325839
    template <class T>
    void TVector3<T>::reflectOnto(const TVector3& other)
    {
        *this -= 2 * this->dot(other) / other.magnitudeSquared() * other;
    }

    template <class T>
    void TVector3<T>::rotate(const Radian& xAngle, const Radian& yAngle, const Radian& zAngle)
    {
        rotate(TQuaternion<T>(zAngle, xAngle, yAngle));
    }

    template <class T>
    void TVector3<T>::rotate(const Radian& angle, const TVector3& axis)
    {
        rotate(TQuaternion<T>(angle, axis));
    }

    template <class T>
    template <class U>
    void TVector3<T>::rotate(const TQuaternion<U>& quaternion)
    {
        TQuaternion<U> tmp{ 0, *this };
        *this = quaternion * tmp * quaternion.inverse();
    }

    template <class T>
    void TVector3<T>::scale(const TVector3& other)
    {
        *this *= other;
    }

    template <class T>
    void TVector3<T>::translate(const TVector3& other)
    {
        *this += other;
    }

    template <class T>
    std::string TVector3<T>::string() const
    {
        std::ostringstream oss;

        oss << "{" << this->m_x << "," << this->m_y << "," << this->m_z << "}";

        return oss.str();
    }

    template <class T>
    std::string TVector3<T>::stringLong() const
    {
        std::ostringstream oss;

        oss << "Vector3{ x:" << this->m_x << ", y:" << this->m_y << ", z:"
            << this->m_z << " }";

        return oss.str();
    }

    template <class T, class U>
    bool operator==(const TVector3<T>& left, const TVector3<U>& right)
    {
        return floatEquals(left.m_x, static_cast<T>(right.m_x))
            && floatEquals(left.m_y, static_cast<T>(right.m_y))
            && floatEquals(left.m_z, static_cast<T>(right.m_z));
    }

    template <class T, class U>
    bool operator!=(const TVector3<T>& left, const TVector3<U>& right)
    {
        return !(left == right);
    }

    template <class T, class U>
    bool operator>(const TVector3<T>& left, const TVector3<U>& right)
    {
        return left.isLongerThan(right);
    }

    template <class T, class U>
    bool operator<(const TVector3<T>& left, const TVector3<U>& right)
    {
        return right > left;
    }

    template <class T, class U>
    bool operator>=(const TVector3<T>& left, const TVector3<U>& right)
    {
        return !(left < right);
    }

    template <class T, class U>
    bool operator<=(const TVector3<T>& left, const TVector3<U>& right)
    {
        return !(left > right);
    }

    template <class T>
    TVector3<T> operator-(const TVector3<T>& vector)
    {
        return { -vector.m_x, -vector.m_y, -vector.m_z };
    }

    template <class T, class U>
    TVector3<T> operator+(TVector3<T> left, const TVector3<U>& right)
    {
        return left += right;
    }

    template <class T, class U>
    TVector3<T> operator-(TVector3<T> left, const TVector3<U>& right)
    {
        return left -= right;
    }

    template <class T, class U>
    TVector3<T> operator*(TVector3<T> left, const TVector3<U>& right)
    {
        return left *= right;
    }

    template <class T, class U>
    TVector3<T> operator/(TVector3<T> left, const TVector3<U>& right)
    {
        return left /= right;
    }

    template <class T, class U>
    TVector3<T> operator+(TVector3<T> vector, U value)
    {
        return vector += value;
    }

    template <class T, class U>
    TVector3<T> operator-(TVector3<T> vector, U value)
    {
        return vector -= value;
    }

    template <class T, class U>
    TVector3<T> operator*(TVector3<T> vector, U scalar)
    {
        return vector *= scalar;
    }

    template <class T, class U>
    TVector3<U> operator*(U scalar, TVector3<T> vector)
    {
        return vector *= scalar;
    }

    template <class T, class U>
    TVector3<T> operator/(TVector3<T> vector, U scalar)
    {
        return vector /= scalar;
    }

    template <class T>
    std::ostream& operator<<(std::ostream& stream, const TVector3<T>& vector)
    {
        return stream << vector.string();
    }

    template <class T>
    std::istream& operator>>(std::istream& stream, TVector3<T>& vector)
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
        while (component < 3 && valStart != 0);

        if (component != 3)
            vector = TVector3<T>::zero();

        return stream;
    }
}

#endif // !__LIBMATH__VECTOR__VECTOR3_INL__
