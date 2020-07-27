#pragma once
class Matrix2D;
class Vector;

class LinearSystem {
protected:
	int mSize;
	Matrix2D* mpA;
	Vector* mpb;
	LinearSystem(const LinearSystem& otherlinearsystem) =  default;
public:
	LinearSystem( const Matrix2D& matrix, const Vector& vector);
	LinearSystem();
	int getSize() {
		return mSize;
	}

	virtual Vector Solve();

};