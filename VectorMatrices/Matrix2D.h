#pragma once
#include <iostream>

class Vector;

class Matrix2D
{
private:
	double** mData;
	int mNumRows;
	int mNumCols;
public:
	Matrix2D(int mNumRows, int mNumCols);
	Matrix2D(const Matrix2D& OtherMatrix2D);
	Matrix2D(std::initializer_list < std::initializer_list < double > > list);
	~Matrix2D();
	int GetNumberOfRows() const;
	int GetNumberOfColumns() const;

	double& operator()(int i, int j);
	Matrix2D operator=(const Matrix2D& otherMatrix2D);
	Matrix2D operator+() const;
	Matrix2D operator-() const;
	Matrix2D operator+(const Matrix2D& otherMatrix2D) const;
	Matrix2D operator-(const Matrix2D& otherMatrix2D) const;
	Matrix2D operator*(double a) const;
	Vector operator*(const Vector& v) const;
	Matrix2D operator*(const Matrix2D& otherMatrix2D) const;
	double CalculateDeterminant() const;
	friend std::ostream& operator<<(std::ostream& output, const Matrix2D& m);
	//friend Vector operator*(const Matrix2D& m, const Vector& v);
	friend Vector operator*(const Vector& v, const Matrix2D& m);

};

Matrix2D operator*(double a, const Matrix2D& othermatrix);

