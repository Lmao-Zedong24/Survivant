#ifndef __LIBMATH__MATRIX__MATRIX2_H__
#define __LIBMATH__MATRIX__MATRIX2_H__

#include "TMatrix.h"

namespace LibMath
{
	template<typename DataT>
	struct Details::Determinant<2, 2, DataT>
	{
		static DataT	compute(const TMatrix<2, 2, DataT>& mat);
	};

	typedef TMatrix<2, 2, float> Matrix2x2;
	typedef Matrix2x2 Matrix2;

	typedef TMatrix<2, 3, float> Matrix2x3;

	typedef TMatrix<2, 4, float> Matrix2x4;
}

#include "Matrix2.inl"

#endif // !__LIBMATH__MATRIX__MATRIX2_H__