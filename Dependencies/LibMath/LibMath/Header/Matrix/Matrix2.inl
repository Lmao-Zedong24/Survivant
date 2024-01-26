#ifndef __LIBMATH__MATRIX__MATRIX2_INL__
#define __LIBMATH__MATRIX__MATRIX2_INL__

#include "Matrix2.h"

namespace LibMath::Details
{
	template <typename DataT>
	DataT Determinant<2, 2, DataT>::compute(const TMatrix<2, 2, DataT>& mat)
	{
		// 0 1
		// 2 3
		return mat[0] * mat[3] - mat[1] * mat[2];
	}
}

#endif // !__LIBMATH__MATRIX__MATRIX2_INL__