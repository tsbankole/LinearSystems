#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include <cmath>
#include <cassert>

Matrix::Matrix(int mNumRows = 1, int mNumCols = 1) {
	this->mNumRows = mNumRows;
	this->mNumCols = mNumCols;
	int matrixsize{ mNumCols * mNumCols };
	mData = new double[matrixsize];
}

Matrix::Matrix(const Matrix& Othermatrix) {
	int matrixsize{ Othermatrix.mNumCols * Othermatrix.mNumRows };
	mNumCols = Othermatrix.mNumCols;
	mNumRows = Othermatrix.mNumRows;
	mData = new double[matrixsize];
	for (int i = 0; i < matrixsize; i++) {
		mData[i] = Othermatrix.mData[i];
	}
}

Matrix::Matrix(std::initializer_list < double > list, int rows, int cols) {
	assert(cols*rows == (int)list.size());
	mNumCols = cols;
	mNumRows = rows;
	mData = new double[rows*cols]; 
	int i = 0;
	for (auto x: list) {
		mData[i] = x;
		i++;
	}
}

Matrix::~Matrix() {
	if(mData) delete[] mData;
}

int Matrix::GetNumberOfColumns() const {
	return mNumCols;
}

int Matrix::GetNumberOfRows() const {
	return mNumRows;
}

double& Matrix::operator()(int i, int j) {
	assert(i <= mNumRows && j <= mNumCols);
	return mData[(i - 1)*mNumCols + (j - 1)];
}

Matrix Matrix::operator=(const Matrix& otherMatrix) {
	assert( mNumCols == otherMatrix.mNumCols && mNumRows == otherMatrix.mNumRows );
	int matrixsize = mNumCols * mNumRows;
	for (int i = 0; i < matrixsize; i++) {
		mData[i] = otherMatrix.mData[i];
	}
	return *this;
}

Matrix Matrix::operator+() const{
	Matrix m(mNumRows, mNumCols);
	m = *this;
	return m;
}

Matrix Matrix::operator-() const {
	Matrix m(mNumRows, mNumCols);
	for (int i = 0; i < mNumRows*mNumCols; i++) {
		m.mData[i] = -mData[i];
	}
	return m;
}

Matrix Matrix::operator+(const Matrix& othermatrix) const {
	assert(mNumCols == othermatrix.mNumCols && mNumRows == othermatrix.mNumRows);
	Matrix m(mNumRows, mNumCols);
	for (int i = 0; i < mNumRows*mNumCols; i++) {
		m.mData[i] = mData[i] + othermatrix.mData[i];
	}
	return m;
}

Matrix Matrix::operator-(const Matrix& othermatrix) const {
	assert(mNumCols == othermatrix.mNumCols && mNumRows == othermatrix.mNumRows);
	Matrix m(mNumRows, mNumCols);
	for (int i = 0; i < mNumRows*mNumCols; i++) {
		m.mData[i] = mData[i] - othermatrix.mData[i];
	}
	return m;
}

Matrix Matrix::operator*(double a) const {
	Matrix m(mNumRows, mNumCols);
	for (int i = 0; i < mNumRows * mNumCols; i++) {
		m.mData[i] = a * mData[i];
	}
	return m;
}

Vector Matrix::operator*(const Vector& v) const {
	assert(mNumRows == v.GetSize());
	Vector result =  Vector(mNumCols);
	for (int i = 0; i < mNumCols; i++) {
		double temp{ 0.0 };
		for (int j = 0; j < mNumRows; j++) {
			temp += v.Read(j) * mData[i + j*mNumCols];
		}
		result[i] = temp;
	}
	return result;
}


Matrix Matrix::operator*(const Matrix& otherMatrix) const {
	assert(mNumCols == otherMatrix.mNumRows);
	Matrix m(mNumRows, otherMatrix.mNumCols);
	int matrixsize{ mNumRows*otherMatrix.mNumCols };
	for (int i = 0; i < matrixsize; i++) {
		double temp = 0.0;
		int startrow = (i / otherMatrix.mNumCols)*mNumCols;
		int startcol = i - (i / otherMatrix.mNumCols)*otherMatrix.mNumCols;
		for (int j = 0; j < mNumCols; j++) {
			temp += mData[i + startrow] * otherMatrix.mData[i * otherMatrix.mNumCols + startcol];
		}
		m.mData[i] = temp;
	}
	return m;
}



double Matrix::CalculateDeterminant() const{
	return 1.0;

}

std::ostream& operator<<(std::ostream& output, const Matrix& m) {
	output << " { ";
	for (int i = 0; i < m.mNumRows * m.mNumCols; i++) {
		output << m.mData[i] << ", ";
	}
	output << "} \n";
	return output;
}