#pragma once
class Matrix2D;
class Vector;

class LinearSystem {
private:
	int mSize;
	Matrix2D* mpA;
	Vector* mpb;
	LinearSystem(const LinearSystem& otherlinearsystem) =  default;
public:
	LinearSystem( Matrix2D matrix, Vector vector);
	LinearSystem();
	int getSize() {
		return mSize;
	}

	virtual Vector Solve();

};