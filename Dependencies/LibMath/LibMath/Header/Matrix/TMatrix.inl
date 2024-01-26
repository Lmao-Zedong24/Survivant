#ifndef __LIBMATH__MATRIX__TMATRIX_INL__
#define __LIBMATH__MATRIX__TMATRIX_INL__
#include <sstream>
#include <stdexcept>

#include "Arithmetic.h"
#include "TMatrix.h"

namespace LibMath
{
    template <length_t Rows, length_t Cols, class DataT>
    constexpr TMatrix<Rows, Cols, DataT>::TMatrix()
    {
        // Builds a matrix filled with zeros
        for (size_t i = 0; i < getSize(); i++)
            m_values[i] = 0;
    }

    template <length_t Rows, length_t Cols, class DataT>
    constexpr TMatrix<Rows, Cols, DataT>::TMatrix(DataT scalar)
    {
        // Builds a diagonal matrix with the given scalar
        for (length_t row = 0; row < Rows; row++)
        {
            for (length_t col = 0; col < Cols; col++)
                (*this)(row, col) = row == col ? scalar : 0;
        }
    }

    template <length_t Rows, length_t Cols, typename DataT>
    constexpr TMatrix<Rows, Cols, DataT>::TMatrix(const TMatrix& other)
    {
        for (size_t i = 0; i < other.getSize(); i++)
            m_values[i] = other[i];
    }

    template <length_t Rows, length_t Cols, typename DataT>
    constexpr TMatrix<Rows, Cols, DataT>::TMatrix(TMatrix&& other) noexcept
    {
        for (size_t i = 0; i < other.getSize(); i++)
            m_values[i] = other[i];
    }

    template <length_t Rows, length_t Cols, typename DataT>
    TMatrix<Rows, Cols, DataT>& TMatrix<Rows, Cols, DataT>::operator=(const TMatrix& other)
    {
        if (this == &other)
            return *this;

        for (size_t i = 0; i < getSize(); i++)
            m_values[i] = other[i];

        return *this;
    }

    template <length_t Rows, length_t Cols, typename DataT>
    TMatrix<Rows, Cols, DataT>& TMatrix<Rows, Cols, DataT>::operator=(TMatrix&& other) noexcept
    {
        if (this == &other)
            return *this;

        for (size_t i = 0; i < other.getSize(); i++)
            m_values[i] = other[i];

        return *this;
    }

    template <length_t Rows, length_t Cols, typename DataT>
    template <typename T>
    TMatrix<Rows, Cols, DataT>::operator TMatrix<Rows, Cols, T>()
    {
        TMatrix<Rows, Cols, T> mat;

        for (size_t i = 0; i < getSize(); i++)
            mat[i] = static_cast<T>(m_values[i]);

        return mat;
    }

    template <length_t Rows, length_t Cols, class DataT>
    constexpr DataT TMatrix<Rows, Cols, DataT>::operator[](size_t index) const
    {
        if (index >= getSize())
            throw std::out_of_range("Index out of range");

        return m_values[index];
    }

    template <length_t Rows, length_t Cols, class DataT>
    DataT& TMatrix<Rows, Cols, DataT>::operator[](size_t index)
    {
        if (index >= getSize())
            throw std::out_of_range("Index out of range");

        return m_values[index];
    }

    template <length_t Rows, length_t Cols, typename DataT>
    DataT TMatrix<Rows, Cols, DataT>::operator()(const length_t row, const length_t column) const
    {
        return (*this)[getIndex(row, column)];
    }

    template <length_t Rows, length_t Cols, typename DataT>
    DataT& TMatrix<Rows, Cols, DataT>::operator()(const length_t row, const length_t column)
    {
        return (*this)[getIndex(row, column)];
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows, Cols, DataT>& TMatrix<Rows, Cols, DataT>::operator+=(const TMatrix& other)
    {
        for (size_t i = 0; i < getSize(); i++)
            m_values[i] += other[i];

        return *this;
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows, Cols, DataT>& TMatrix<Rows, Cols, DataT>::operator-=(const TMatrix& other)
    {
        for (size_t i = 0; i < getSize(); i++)
            m_values[i] -= other[i];

        return *this;
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows, Cols, DataT>& TMatrix<Rows, Cols, DataT>::operator*=(const TMatrix& other)
    {
        return (*this = *this * other);
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows, Cols, DataT>& TMatrix<Rows, Cols, DataT>::operator/=(const TMatrix& other)
    {
        return (*this = *this / other);
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows, Cols, DataT>& TMatrix<Rows, Cols, DataT>::operator+=(DataT scalar)
    {
        for (size_t i = 0; i < getSize(); i++)
            m_values[i] += scalar;

        return *this;
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows, Cols, DataT>& TMatrix<Rows, Cols, DataT>::operator-=(DataT scalar)
    {
        for (size_t i = 0; i < getSize(); i++)
            m_values[i] -= scalar;

        return *this;
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows, Cols, DataT>& TMatrix<Rows, Cols, DataT>::operator*=(DataT scalar)
    {
        for (size_t i = 0; i < getSize(); i++)
            m_values[i] *= scalar;

        return *this;
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows, Cols, DataT>& TMatrix<Rows, Cols, DataT>::operator/=(DataT scalar)
    {
        for (size_t i = 0; i < getSize(); i++)
            m_values[i] /= scalar;

        return *this;
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows, Cols, DataT> TMatrix<Rows, Cols, DataT>::operator+(const TMatrix& other) const
    {
        TMatrix mat = *this;
        return mat += other;
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows, Cols, DataT> TMatrix<Rows, Cols, DataT>::operator-(const TMatrix& other) const
    {
        TMatrix mat = *this;
        return mat -= other;
    }

    template <length_t Rows, length_t Cols, class DataT>
    template <length_t OtherRows, length_t OtherCols>
    TMatrix<Rows, OtherCols, DataT> TMatrix<Rows, Cols, DataT>::operator*(const TMatrix<OtherRows, OtherCols, DataT>& other) const
    {
        static_assert(OtherRows == Cols, "Can't multiply matrices with incompatible sizes");

        TMatrix<Rows, OtherCols, DataT> result;

        for (length_t otherCol = 0; otherCol < OtherCols; otherCol++)
        {
            for (length_t row = 0; row < Rows; row++)
            {
                DataT scalar = 0;

                for (length_t col = 0; col < Cols; col++)
                    scalar += (*this)(row, col) * other(col, otherCol);

                result(row, otherCol) = scalar;
            }
        }

        return result;
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows, Cols, DataT> TMatrix<Rows, Cols, DataT>::operator/(const TMatrix& other) const
    {
        return *this * other.inverse();
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows, Cols, DataT> TMatrix<Rows, Cols, DataT>::operator+(DataT scalar) const
    {
        TMatrix mat = *this;
        return mat += scalar;
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows, Cols, DataT> TMatrix<Rows, Cols, DataT>::operator-(DataT scalar) const
    {
        TMatrix mat = *this;
        return mat -= scalar;
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows, Cols, DataT> TMatrix<Rows, Cols, DataT>::operator*(DataT scalar) const
    {
        TMatrix mat = *this;
        return mat *= scalar;
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows, Cols, DataT> TMatrix<Rows, Cols, DataT>::operator/(DataT scalar) const
    {
        TMatrix mat = *this;
        return mat /= scalar;
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows, Cols, DataT> TMatrix<Rows, Cols, DataT>::operator-() const
    {
        return *this * -1;
    }

    template <length_t Rows, length_t Cols, class DataT>
    constexpr bool TMatrix<Rows, Cols, DataT>::operator==(const TMatrix& other) const
    {
        if (other.getRowCount() != Rows || other.getColumnCount() != Cols)
            return false;

        for (size_t i = 0; i < getSize(); i++)
        {
            if (!floatEquals(m_values[i], other[i]))
                return false;
        }

        return true;
    }

    template <length_t Rows, length_t Cols, class DataT>
    constexpr bool TMatrix<Rows, Cols, DataT>::operator!=(const TMatrix& other) const
    {
        return !(*this == other);
    }

    template <length_t Rows, length_t Cols, class DataT>
    bool TMatrix<Rows, Cols, DataT>::isIdentity() const
    {
        if constexpr (Rows != Cols)
            return false;

        return *this == TMatrix(1.f);
    }

    template <length_t Rows, length_t Cols, class DataT>
    constexpr length_t TMatrix<Rows, Cols, DataT>::getRowCount()
    {
        return Rows;
    }

    template <length_t Rows, length_t Cols, class DataT>
    constexpr length_t TMatrix<Rows, Cols, DataT>::getColumnCount()
    {
        return Cols;
    }

    template <length_t Rows, length_t Cols, typename DataT>
    constexpr size_t TMatrix<Rows, Cols, DataT>::getSize()
    {
        return static_cast<size_t>(Rows) * Cols;
    }

    template <length_t Rows, length_t Cols, class DataT>
    length_t TMatrix<Rows, Cols, DataT>::getIndex(const length_t row, const length_t column)
    {
        if (row < 0 || row >= Rows || column < 0 || column >= Cols)
            throw std::out_of_range("Index out of range");

        return row * Cols + column;
    }

    template <length_t Rows, length_t Cols, class DataT>
    DataT* TMatrix<Rows, Cols, DataT>::getArray()
    {
        return m_values;
    }

    template <length_t Rows, length_t Cols, class DataT>
    const DataT* TMatrix<Rows, Cols, DataT>::getArray() const
    {
        return m_values;
    }

    template <length_t Rows, length_t Cols, class DataT>
    DataT TMatrix<Rows, Cols, DataT>::determinant() const
    {
        return Details::Determinant<Rows, Cols, DataT>::compute(*this);
    }

    template <length_t Rows, length_t Cols, class DataT>
    DataT TMatrix<Rows, Cols, DataT>::cofactor(const length_t row, const length_t column) const
    {
        static_assert(Rows == Cols, "Can't compute the cofactor of a non-square matrix");

        if constexpr (Rows == 1)
            return m_values[0];

        // The multiplier is (-1)^(i+j) so 1 when i + j is pair and -1 otherwise
        const DataT multiplier = (row + column) % 2 == 0 ? static_cast<DataT>(1) : static_cast<DataT>(-1);

        return multiplier * minor(row, column).determinant();
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows - 1, Cols - 1, DataT> TMatrix<Rows, Cols, DataT>::minor(const length_t row, const length_t column) const
    {
        TMatrix<Rows - 1, Cols - 1, DataT> minor;
        length_t                           minorLine = 0;

        for (length_t i = 0; i < Rows; i++)
        {
            if (i == row)
                continue;

            length_t minorCol = 0;

            for (length_t j = 0; j < Cols; j++)
            {
                if (j == column)
                    continue;

                minor(minorLine, minorCol++) = (*this)(i, j);
            }

            minorLine++;
        }

        return minor;
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Cols, Rows, DataT> TMatrix<Rows, Cols, DataT>::transposed() const
    {
        TMatrix<Cols, Rows, DataT> transposed;

        for (length_t i = 0; i < Rows; i++)
        {
            for (length_t j = 0; j < Cols; j++)
                transposed(j, i) = (*this)(i, j);
        }

        return transposed;
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows, Cols, DataT> TMatrix<Rows, Cols, DataT>::coMatrix() const
    {
        static_assert(Rows == Cols, "Can't compute the co-matrix of a non-square matrix");

        TMatrix<Rows, Cols, DataT> coMatrix;

        for (length_t row = 0; row < Rows; row++)
        {
            for (length_t col = 0; col < Cols; col++)
                coMatrix(row, col) = cofactor(row, col);
        }

        return coMatrix;
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Cols, Rows, DataT> TMatrix<Rows, Cols, DataT>::adjugate() const
    {
        return coMatrix().transposed();
    }

    template <length_t Rows, length_t Cols, class DataT>
    TMatrix<Rows, Cols, DataT> TMatrix<Rows, Cols, DataT>::inverse() const
    {
        static_assert(Rows == Cols, "Can't invert a non-square matrix");

        const DataT det = determinant();

        if (det == 0.f)
            throw Exceptions::NonInvertibleMatrix();

        return adjugate() / det;
    }

    template <length_t Rows, length_t Cols, typename DataT>
    std::string TMatrix<Rows, Cols, DataT>::string() const
    {
        std::ostringstream oss;
        oss << '{';

        for (size_t i = 0; i < getSize(); ++i)
        {
            oss << m_values[i];

            if (i + 1 < getSize())
                oss << ',';
        }

        oss << '}';
        return oss.str();
    }

    template <length_t Rows, length_t Cols, typename DataT>
    std::string TMatrix<Rows, Cols, DataT>::stringLong() const
    {
        std::ostringstream oss;
        oss << "Matrix" << Rows << 'x' << Cols << "{ ";

        for (length_t row = 0; row < Rows; ++row)
        {
            for (length_t col = 0; col < Cols; ++col)
            {
                oss << row << '_' << col << ": " << (*this)(row, col);

                if (row + 1 < Rows || col + 1 < Cols)
                    oss << ", ";
            }
        }

        oss << " }";
        return oss.str();
    }

    template <length_t Rows, length_t Cols, typename DataT>
    std::ostream& operator<<(std::ostream& stream, const TMatrix<Rows, Cols, DataT>& mat)
    {
        return stream << mat.string();
    }

    template <length_t Rows, length_t Cols, typename DataT>
    std::istream& operator>>(std::istream& stream, TMatrix<Rows, Cols, DataT>& mat)
    {
        std::string line;

        std::getline(stream, line, '}');

        size_t component = 0;
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

            mat[component] = std::stof(line.substr(valStart));

            valStart = line.find(',', valStart) + 1;
            component++;
        }
        while (component < mat.getSize() && valStart != 0);

        if (component != mat.getSize())
            mat = TMatrix<Rows, Cols, DataT>(1);

        return stream;
    }

    template <length_t Rows, length_t Cols, typename DataT>
    DataT Details::Determinant<Rows, Cols, DataT>::compute(const TMatrix<Rows, Cols, DataT>& mat)
    {
        static_assert(Rows == Cols, "Can't compute the determinant of a non-square matrix");

        if constexpr (Rows == 1)
            return mat[0];

        DataT determinant = 0;

        for (length_t col = 0; col < Cols; col++)
            determinant += mat[col] * mat.cofactor(0, col);

        return determinant;
    }
}

#endif // !__LIBMATH__MATRIX__TMATRIX_INL__
