// VectorMatrices.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Vector.h"
#include <cmath>
#include <cassert>

//Overridden copy constructor
// Allocates memory for new vector, and copies
// entries of other vector into it

Vector::Vector(const Vector& otherVector) {
	//delete[] mData;
	mSize = otherVector.GetSize();
	mData = new double[mSize];
	for (int i = 0; i < mSize; i++) {
		mData[i] = otherVector.mData[i];
	}
}

Vector::Vector(int size) {
	assert(size > 0);
	mSize = size;
	mData = new double[mSize];
	for (int i = 0; i < size; i++) {
		mData[i] = 0.0;
	}
}

Vector::Vector(std::initializer_list<double> list): Vector((int) list.size()) {
	int i = 0;
	for (auto x : list) {
		mData[i] = x;
		++i;
	}
}

Vector::~Vector() {
	delete[] mData;
}

int Vector::GetSize() const {
	return mSize;
}


double& Vector::operator[](int i) {
	assert(i < mSize && i > -1 );
	return mData[i];
}

double Vector::Read(int i) const {
	//assert(i < mSize && i > -1);
	return mData[i];
}

void Vector::Write(int i, double val) {
	mData[i] = val;
}

double Vector::operator()(int i) const{
	//assert(i <= mSize && i > 1);
	return mData[i];
}

// Overloading the assignment operator
Vector& Vector::operator=(const Vector& otherVector)
{
	assert(mSize == otherVector.mSize);
	for (int i = 0; i < mSize; i++){
		mData[i] = otherVector.mData[i];
	}
	return *this;
 }


// Overloading the unary + operator
Vector Vector::operator+() const{
	Vector v(mSize);
	v = *this;
	return v;
}


// Overloading the unary - operator
Vector Vector::operator-() const{
	Vector v(mSize);
	for (int i = 0; i < mSize; i++){
		v[i] = -mData[i];
	}
	return v;
}

// Overloading the binary + operator
Vector Vector::operator+(const Vector& v1) const{
    assert(mSize == v1.mSize);
	Vector v(mSize);
	for(int i = 0; i < mSize; i++){
        v[i] = mData[i] + v1.mData[i];
	}
	return v;
}

// Overloading the binary + operator
Vector Vector::operator-(const Vector& v1) const{
	assert(mSize == v1.mSize);
	Vector v(mSize);
	for (int i = 0; i < mSize; i++) {
		v[i] = mData[i] - v1.mData[i];
	}
	return v;
}

//Overloading scalar multiplication
Vector Vector::operator*(double a) const {
	Vector v  = Vector(mSize);
	for (int i = 0; i < mSize; ++i) {
		v.mData[i] = mData[i] * a;
	}
	return v;
}

//Method to calculate norm (with default value p = 2)
// corresponding to the Euclidean norm
double Vector::CalculateNorm(int p) const {
	double norm{ 0.0 }, sum{0.0};
	for (int i = 0; i < mSize; ++i) {
		sum += pow(fabs(mData[i]), p);
	}
	return pow(sum, 1.0/((double) p));
}

int length(const Vector& v) {
	return v.mSize;
}

double inner(const Vector& v1, const Vector& v2) {
	assert(v1.mSize == v2.mSize);
	double temp = 0.0;
	for (int i = 0; i < v1.mSize; i++) {
		temp += v1(i) * v2(i);
	}
	return temp;
}

std::ostream& operator<<(std::ostream& output, const Vector& v) {
	output << " { ";
	int i = 0;
	for (; i < v.mSize-1; i++) {
		output << v.mData[i] << ", ";
	}
	output << v.mData[i] << " } \n";
	return output;
}




