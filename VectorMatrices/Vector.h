#pragma once
#include <iostream>
class Vector
{
private:
	double* mData; // data stored in vector
	int mSize; // size of vector 
public:
	Vector(const Vector& otherVector);
	Vector(int size);
	Vector(std::initializer_list<double> list);
	~Vector();
	int GetSize() const;
	double& operator[](int i); // zero-based indexing
	
	double Read(int i) const; // read-only zero-based indexing
	void Write(int i, double val);
	double& operator()(int i); // one-based indexing // assignment
	Vector& operator=(const Vector& otherVector);
	Vector operator+() const; // unary +
	Vector operator-() const; // unary -
	Vector operator+(const Vector& v1) const; // binary +
	Vector operator-(const Vector& v1) const; // binary -
								  
	Vector operator*(double a) const; // scalar multiplication
	
	double CalculateNorm(int p = 2) const; // p-norm method
	// declare length function as a friend
	friend int length(const Vector& v); 
	friend std::ostream& operator<<(std::ostream& output, const Vector& v);
	};

// Prototype signature of length() friend function
//int length(const Vector& v);