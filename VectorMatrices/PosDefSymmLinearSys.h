#pragma once
#include "LinearSystem.h"
class Vector;
class Matrix2D;


class PoSDefSymmLinearSys : public LinearSystem {

public:
	PoSDefSymmLinearSys(const Matrix2D& A, const Vector& b);
	Vector solve();
};