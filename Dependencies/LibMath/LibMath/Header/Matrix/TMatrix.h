#ifndef __LIBMATH__MATRIX__TMATRIX_H__
#define __LIBMATH__MATRIX__TMATRIX_H__
#include <exception>
#include <string>

namespace LibMath
{
    namespace Exceptions
    {
        class NonInvertibleMatrix : public std::exception
        {
        public:
            NonInvertibleMatrix() noexcept
                : exception()
            {
            }

            [[nodiscard]] inline const char* what() const noexcept override
            {
                return "Non-invertible matrix";
            }
        };
    }

    using length_t = int;

    template <length_t Rows, length_t Cols, typename DataT>
    class TMatrix
    {
        static_assert(std::is_arithmetic_v<DataT>, "Invalid matrix - data type should be an arithmetic type");
        static_assert(Rows > 0, "Invalid matrix - row count should be greater than zero");
        static_assert(Cols > 0, "Invalid matrix - column count should be greater than zero");

    public:
        constexpr          TMatrix();
        explicit constexpr TMatrix(DataT scalar);
        constexpr          TMatrix(const TMatrix& other);
        constexpr          TMatrix(TMatrix&& other) noexcept;
        ~TMatrix() = default;

        TMatrix& operator=(const TMatrix& other);
        TMatrix& operator=(TMatrix&& other) noexcept;

        template <typename T>
        operator TMatrix<Rows, Cols, T>();

        constexpr DataT operator[](size_t index) const;
        DataT&          operator[](size_t index);

        DataT  operator()(length_t row, length_t column) const;
        DataT& operator()(length_t row, length_t column);

        TMatrix& operator+=(const TMatrix& other);
        TMatrix& operator-=(const TMatrix& other);

        TMatrix& operator*=(const TMatrix& other);
        TMatrix& operator/=(const TMatrix& other);

        TMatrix& operator+=(DataT scalar);
        TMatrix& operator-=(DataT scalar);
        TMatrix& operator*=(DataT scalar);
        TMatrix& operator/=(DataT scalar);

        TMatrix operator+(const TMatrix& other) const;
        TMatrix operator-(const TMatrix& other) const;

        template <length_t OtherRows, length_t OtherCols>
        TMatrix<Rows, OtherCols, DataT> operator*(const TMatrix<OtherRows, OtherCols, DataT>& other) const;
        TMatrix                         operator/(const TMatrix& other) const;

        TMatrix operator+(DataT scalar) const;
        TMatrix operator-(DataT scalar) const;
        TMatrix operator*(DataT scalar) const;
        TMatrix operator/(DataT scalar) const;

        TMatrix operator-() const;

        constexpr bool operator==(const TMatrix& other) const;
        constexpr bool operator!=(const TMatrix& other) const;
        bool           isIdentity() const;

        static constexpr length_t getRowCount();
        static constexpr length_t getColumnCount();
        static constexpr size_t   getSize();

        static length_t getIndex(length_t row, length_t column);

        DataT*       getArray();
        const DataT* getArray() const;

        DataT determinant() const;
        DataT cofactor(length_t row, length_t column) const;

        TMatrix<Rows - 1, Cols - 1, DataT> minor(length_t row, length_t column) const;
        TMatrix<Cols, Rows, DataT>         transposed() const;
        TMatrix<Rows, Cols, DataT>         coMatrix() const;
        TMatrix<Cols, Rows, DataT>         adjugate() const;
        TMatrix<Rows, Cols, DataT>         inverse() const;

        std::string string() const;
        std::string stringLong() const;

    private:
        DataT m_values[Rows * Cols];
    };

    template <length_t Rows, length_t Cols, typename DataT>
    std::ostream& operator<<(std::ostream& stream, const TMatrix<Rows, Cols, DataT>& mat);

    template <length_t Rows, length_t Cols, typename DataT>
    std::istream& operator>>(std::istream& stream, TMatrix<Rows, Cols, DataT>& mat);

    namespace Details
    {
        template <length_t Rows, length_t Cols, typename DataT>
        struct Determinant
        {
            static DataT compute(const TMatrix<Rows, Cols, DataT>& mat);
        };
    }
}

#include "TMatrix.inl"

#endif // !__LIBMATH__MATRIX_TMATRIX_H__
