#pragma once
#include <iostream>

class Vector;

class Matrix
{
private:
	double* mData;
	int mNumRows;
	int mNumCols;
public:
	Matrix(int mNumRows, int mNumCols );
	Matrix(const Matrix& OtherMatrix);
	Matrix(std::initializer_list < double > list, int rows, int cols);
	~Matrix(); 
	int GetNumberOfRows() const;
	int GetNumberOfColumns() const;
	
	double& operator()(int i, int j);
	Matrix operator=(const Matrix& otherMatrix);
	Matrix operator+() const;
	Matrix operator-() const;
	Matrix operator+(const Matrix& otherMatrix) const;
	Matrix operator-(const Matrix& otherMatrix) const;
	Matrix operator*(double a) const;
	Vector operator*(const Vector& v) const;
	Matrix operator*(const Matrix& otherMatrix) const;
	double CalculateDeterminant() const;
	friend std::ostream& operator<<(std::ostream& output, const Matrix& m);

};

