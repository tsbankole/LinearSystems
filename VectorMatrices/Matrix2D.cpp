#include <iostream>
#include "Vector.h"
#include "Matrix2D.h"
#include <cmath>
#include <cassert>

Matrix2D::Matrix2D(int mNumRows = 1, int mNumCols = 1) {
	assert(mNumCols > 0 && mNumRows > 0);
	this->mNumRows = mNumRows;
	this->mNumCols = mNumCols;
	int Matrix2Dsize{ mNumCols * mNumCols };
	mData = new double*[mNumRows];
	for (int i = 0; i < mNumCols; i++) {
		mData[i] = new double[mNumCols];
		for (int j = 0; j < mNumCols; j++) {
			mData[i][j] = 0.0;
		}
	}
}

Matrix2D::Matrix2D(const Matrix2D& OtherMatrix2D) {
	mNumCols = OtherMatrix2D.mNumCols;
	mNumRows = OtherMatrix2D.mNumRows;
	mData = new double*[mNumRows];
	for (int i = 0; i < mNumRows; i++) {
		for (int j = 0; j < mNumCols; j++) {
			mData[i][j] = OtherMatrix2D.mData[i][j];
		}
		
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
	for (int i = 0; i < mNumRows; i++) {
		delete[] mData[i];
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
	assert(i > 0 && i <= mNumCols && j > 0 && j <= mNumCols);
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
	assert(mNumCols== v.GetSize());
	Vector result = Vector(mNumRows);
	for (int i = 0; i < mNumRows; i++) {
		double temp{ 0.0 };
		for (int j = 0; j < mNumCols; j++) {
			temp += v.Read(j) * mData[i][j];
		}
		result[i] = temp;
	}
	return result;
}

Vector operator*(const Vector& v, const Matrix2D& m) {
	int cols = m.GetNumberOfColumns;
	int rows = m.GetNumberOfRows;
	assert(cols == v.GetSize());
	Vector result = Vector(cols);
	for (int i = 0; i < cols; i++) {
		double temp{ 0.0 };
		for (int j = 0; j < rows; j++) {
			temp += v.Read(j) * m.mData[i][j];
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


// Calculate determinant of square matrix recursively
double Matrix2D::CalculateDeterminant() const
{
	assert(mNumRows == mNumCols);
	double determinant = 0.0;
	if (mNumRows == 1)
	{
		determinant = mData[0][0];
	}
	else
	{   // More than one entry of matrix
		for (int i_outer = 0; i_outer < mNumRows; i_outer++)
		{
			Matrix2D sub_matrix(mNumRows - 1, mNumRows - 1);
			for (int i = 0; i < mNumRows - 1; i++)
			{
				for (int j = 0; j < i_outer; j++)
				{
					sub_matrix(i + 1, j + 1) = mData[i + 1][j];
				}
				for (int j = i_outer; j < mNumRows - 1; j++)
				{
					sub_matrix(i + 1, j + 1) = mData[i + 1][j + 1];
				}
			}
			double sub_matrix_determinant =	sub_matrix.CalculateDeterminant();
			determinant += pow(-1.0, i_outer) *	mData[0][i_outer] * sub_matrix_determinant;
		}
	}
	return determinant;
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

Matrix2D operator*(double a, const Matrix2D& othermatrix ){
	return othermatrix*a;
}