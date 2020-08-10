#include<cmath>
#include<cassert>
#include<iostream>
#include <vector>
#include "Vector.h"
#include "Matrix2D.h"
#include "LinearSystem.h"
#include "mkl.h"


LinearSystem::LinearSystem(const Matrix2D& A, const Vector& b) {
	mSize = b.GetSize();
	assert(mSize == A.GetNumberOfRows());
	assert(mSize == A.GetNumberOfColumns());
	mpA = new Matrix2D(A);
	mpb = new Vector(b);
}


LinearSystem::~LinearSystem() {
	delete mpA;
	delete mpb;
}


Vector LinearSystem::Solve()
{
	Matrix2D rA = *mpA;
	Vector rb = *mpb;
	Vector m(mSize);
	Vector solution(mSize);
	
	// forward sweep of Gaussian elimination
	for (int k = 0; k < mSize - 1; k++) {
		// see if pivoting is necessary
		double max = 0.0;
		int row = -1;
		for (int i = k; i < mSize; i++) {
			if (fabs(rA[i][k]) > max) {
				row = i;
			}
		}
		assert(row > 0);

		// pivot if necessary
		if (row != k) {
			// swap matrix rows k+1 with row+1
			for (int i = 0; i < mSize; i++) {
				double temp = rA[k][i];
				rA[k][i] = rA[row][i];
				rA[row][i] = temp;
			}
			// swap vector entries k+1 with row+1
			double temp = rb[k];
			rb[k] = rb[row];
			rb[row] = temp;
		}

		// create zeros in lower part of column k
		for (int i = k + 1; i < mSize; i++) {
			m[i] = rA[i][k] / rA[k][k];
			for (int j = k; j < mSize; j++) {
				rA[i][j] -= rA[k][j] * m[i];
			}
			rb[i] -= rb[k] * m[i];
		}
	}

	// back substitution
	for (int i = mSize - 1; i > -1; i--){
		solution[i] = rb[i];
		for (int j = i + 1; j < mSize; j++) {
			solution[i] -= rA[i][j]*solution[j];
		}
		solution[i] /= rA[i][i];
	}

	return solution;
}


Vector LinearSystem::SolveMKL() {
	Matrix2D rA = *mpA;
	Vector rb = *mpb;

	double* A = (double *)mkl_malloc(mSize*mSize * sizeof(double), 64);
	double* b = (double *)mkl_malloc(mSize * sizeof(double), 64);
	for (size_t i = 0; i < mSize; i++) {
		for (size_t j = 0; j < mSize; j++) {
			A[i*mSize + j] = rA[i][j];
		}
		b[i] = rb[i];
	}

	int* ipiv = new int[mSize];
	
	LAPACKE_dgesv(LAPACK_ROW_MAJOR, mSize, 1, A, mSize, ipiv, b, 1);
	
	// copy back the solution from the matrix b into the Vector to be returned
	for (size_t i = 0; i < mSize; i++) {
		rb[i] = b[i];
	}

	delete [] ipiv;
	return rb;

}