#include"Vector.h";
#include "Matrix.h"
#include<string>
#include<cassert>
#include<iostream>

using namespace std;

int main(){

	// test constructor
	Vector v1{ 1,2,3,4,5 };
	Vector v2 = v1 * 2.0;
	cout << v2;
    //	cout << v1;
	/*
	Vector v2{ 2,3,4,5,6 };
	cout << v2;

	//cout << Vector(v2 - v1);
	
	Vector v3(v2);
	cout << v3;
	
	Vector v4 = v2 + v3;
	cout << v4;

	Vector v5(5);
	v5 = v2;
	cout << v5;
	Vector v6 = v2 - v3;
	cout << v6; 

	Vector v7{ -v4 };
	cout << v7;

	cout << v7.CalculateNorm(1); */

	/*****testing matrices **********/

	Matrix m1{ {1,2,3,4},2,2 };
	cout << m1;

	Matrix m2{ {2,3,4,5}, 2,2 };

	Matrix m3 = m2 - m1;
	cout << m3;

	Matrix m4 = m2 + m1;
	cout << m4;

	Matrix m5 = m4*2.0;
	cout << m5;

	Matrix m6{ {1.0,2.0,3.0,4.0,5.0,-1.0,-2.0,-3.0,-4.0,-5.0}, 5,2 };
	cout << m6;
	Vector v3 = m6 * v2;
	cout << v3;
	return 0;
}