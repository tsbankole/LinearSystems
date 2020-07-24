#include <iostream>
#include "Vector.h"
#include "Matrix2D.h"
#include <cmath>
#include <cassert>

Matrix2D::Matrix2D(int mNumRows = 1, int mNumCols = 1) {
	this->mNumRows = mNumRows;
	this->mNumCols = mNumCols;
	int Matrix2Dsize{ mNumCols * mNumCols };
	mData = new double*[mNumRows];
	for (int i = 0; i < mNumCols; i++) {
		mData[i] = new double[mNumCols];
	}
}

Matrix2D::Matrix2D(const Matrix2D& OtherMatrix2D) {
	mNumCols = OtherMatrix2D.mNumCols;
	mNumRows = OtherMatrix2D.mNumRows;
	mData = new double*[mNumCols];
	for (int i = 0; i < mNumRows; i++) {
		mData[i] = new double[mNumCols];
	}
}

Matrix2D::Matrix2D(std::initializer_list < std::initializer_list < double > > list) {
	int numrows{ (int)list.size() };
	int numcols{ (int)list.begin()[0].size() };
	for (int i = 1; i < list.size(); i++) {
		assert(list.begin()[i].size() == list.begin()[i - 1].size());
	}
	mNumRows = numrows;
	mNumCols = numcols;
	mData = new double*[numrows];

	for (int i = 0; i < numrows; i++) {
		for (int j = 0; j < numcols; j++) {
			mData[i][j] = list.begin()[i].begin()[j];
		}
	}
}

Matrix2D::~Matrix2D() {
	for (int j = 0; j < mNumCols; j++) {
		delete[] mData[j];
	}
	delete[] mData;
}

int Matrix2D::GetNumberOfColumns() const {
	return mNumCols;
}

int Matrix2D::GetNumberOfRows() const {
	return mNumRows;
}

double& Matrix2D::operator()(int i, int j) {
	assert(i <= mNumCols && j <= mNumCols);
	return mData[i-1][j-1];
}

Matrix2D Matrix2D::operator=(const Matrix2D& otherMatrix2D) {
	assert(mNumCols == otherMatrix2D.mNumCols && mNumRows == otherMatrix2D.mNumRows);
	for (int i = 0; i < mNumRows; i++) {
		for (int j = 0; j < mNumCols; j++) {
			mData[i][j] = otherMatrix2D.mData[i][j];
		}
	}
	return *this;
}

Matrix2D Matrix2D::operator+() const {
	Matrix2D m(mNumRows, mNumCols);
	m = *this;
	return m;
}

Matrix2D Matrix2D::operator-() const {
	Matrix2D m(mNumRows, mNumCols);
	for (int i = 0; i < mNumRows; i++) {
		for (int j = 0; j < mNumCols; j++) {
			m.mData[i][j] = -mData[i][j];
		}
	}
	return m;
}

Matrix2D Matrix2D::operator+(const Matrix2D& otherMatrix2D) const {
	assert(mNumCols == otherMatrix2D.mNumCols && mNumRows == otherMatrix2D.mNumRows);
	Matrix2D m(mNumRows, mNumCols);
	for (int i = 0; i < mNumRows; i++) {
		for (int j = 0; j < mNumCols; j++) {
			m.mData[i][j] = mData[i][j] + otherMatrix2D.mData[i][j];
		}
	}
	return m;
}

Matrix2D Matrix2D::operator-(const Matrix2D& otherMatrix2D) const {
	assert(mNumCols == otherMatrix2D.mNumCols && mNumRows == otherMatrix2D.mNumRows);
	Matrix2D m(mNumRows, mNumCols);
	for (int i = 0; i < mNumRows; i++) {
		for (int j = 0; j < mNumCols; j++) {
			m.mData[i][j] = mData[i][j] - otherMatrix2D.mData[i][j];
		}
	}
	return m;
}

Matrix2D Matrix2D::operator*(double a) const {
	Matrix2D m(mNumRows, mNumCols);
	for (int i = 0; i < mNumRows; i++) {
		for (int j = 0; j < mNumCols; j++) {
			m.mData[i][j] = a * mData[i][j];
		}
	}
	return m;
}

Vector Matrix2D::operator*(const Vector& v) const {
	assert(mNumRows == v.GetSize());
	Vector result = Vector(mNumCols);
	for (int i = 0; i < mNumCols; i++) {
		double temp{ 0.0 };
		for (int j = 0; j < mNumRows; j++) {
			temp += v.Read(j) * mData[i][j];
		}
		result[i] = temp;
	}
	return result;
}


Matrix2D Matrix2D::operator*(const Matrix2D& otherMatrix2D) const {
	assert(mNumCols == otherMatrix2D.mNumRows);
	Matrix2D m(mNumRows, otherMatrix2D.mNumCols);
	
	for (int i = 0; i < mNumRows; i++) {
		for (int j = 0; j < mNumCols; j++) {
			double temp = 0.0;
			for (int k = 0; k < mNumCols; k++) {
				temp += mData[i][k] * otherMatrix2D.mData[k][j];
			}
			m.mData[i][j] = temp;
		}
	}
	return m;
}


double Matrix2D::CalculateDeterminant() const {
	return 1.0;

}

std::ostream& operator<<(std::ostream& output, const Matrix2D& m) {
	output << " { ";
	for (int i = 0; i < m.mNumRows; i++) {
		output << " { ";
		int j = 0;
		for (; j < m.mNumCols-1; j++) {
			output << m.mData[i][j] << ", ";
		}
		output << m.mData[i][j] << " } ";
	}
	output << "} \n";
	return output;
}

