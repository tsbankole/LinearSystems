#include<cmath>
#include<cassert>
#include<iostream>
#include "Vector.h"
#include "Matrix2D.h"
#include "LinearSystem.h"
#include "PosDefSymmLinearSys.h"
#include "pch.h"

PoSDefSymmLinearSys::PoSDefSymmLinearSys(const Matrix2D& A, const Vector& b) {
	mSize = b.GetSize();
	assert(mSize == A.GetNumberOfRows());
	for (int i = 0; i < A.GetNumberOfRows() -1; i++) {
		for (int j = i + 1; j < A.GetNumberOfColumns(); j++) {
			assert(A(i, j) == A(j, i));
		}
	}
	mpA = new Matrix2D(A);
	mpb = new Vector(b);
}

Vector PoSDefSymmLinearSys::solve() {
	int k = 0;
	Matrix2D rA = *mpA;
	Vector rb = *mpb;

	Vector x(mpb->GetSize());
	double beta = 0.0; double alpha = 0.0;
	Vector r{ rb - rA * x };
	Vector rprev(r);
	Vector p(r);
	double eps = 0.0001;
	
	while (r.CalculateNorm() > eps) {
		alpha = inner(r,r)/inner(p, rA*p); 
		x = x + p * alpha;
		rprev = r;
		r = r - alpha * rA * p;
		if (k > 0) {
			beta = inner(r, r) / inner(rprev, rprev);
		}
		p = r + p * beta;
		k++;
		std::cout << x << " " << r.CalculateNorm() <<  " " << "\n";
	}
	return x;
}