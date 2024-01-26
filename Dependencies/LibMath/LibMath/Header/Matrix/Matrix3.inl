#ifndef __LIBMATH__MATRIX__MATRIX3_INL__
#define __LIBMATH__MATRIX__MATRIX3_INL__

#include "Matrix3.h"

namespace LibMath::Details
{
	template <typename DataT>
	DataT Determinant<3, 3, DataT>::compute(const TMatrix<3, 3, DataT>& mat)
	{
		// 0 1 2
		// 3 4 5
		// 6 7 8
		const DataT positive = mat[0] * mat[4] * mat[8] +
			mat[1] * mat[5] * mat[6] +
			mat[2] * mat[3] * mat[7];

		const DataT negative = mat[2] * mat[4] * mat[6] +
			mat[1] * mat[3] * mat[8] +
			mat[0] * mat[5] * mat[7];

		return positive - negative;
	}
}

#endif // !__LIBMATH__MATRIX__MATRIX3_INL__
