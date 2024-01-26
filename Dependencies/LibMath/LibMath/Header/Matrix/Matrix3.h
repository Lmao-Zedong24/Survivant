#ifndef __LIBMATH__MATRIX__MATRIX3_H__
#define __LIBMATH__MATRIX__MATRIX3_H__

#include "TMatrix.h"

namespace LibMath
{
	template<typename DataT>
	struct Details::Determinant<3, 3, DataT>
	{
		static DataT	compute(const TMatrix<3, 3, DataT>& mat);
	};

	typedef TMatrix<3, 2, float> Matrix3x2;

	typedef TMatrix<3, 3, float> Matrix3x3;
	typedef Matrix3x3 Matrix3;

	typedef TMatrix<3, 4, float> Matrix3x4;
}

#include "Matrix3.inl"

#endif // !__LIBMATH__MATRIX__MATRIX3_H__
