#include"Vector.h";
#include "Matrix.h"
#include "Matrix2D.h"|
#include<string>
#include<cassert>
#include<iostream>

using namespace std;

int main(){

	// test constructor
	Vector v1{ 1,2,3 };
	Vector v2 = v1 * 2.0;
	//cout << v2;
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

	Matrix2D m{ {1,2,3}, {4,5,6}, {7,8,9} , {0,-1,-2} };

	cout << m << m.GetNumberOfColumns() << m.GetNumberOfRows();

	Matrix2D m1 = m;

	cout << m1;

	Matrix2D m2(4, 3);
	m2= +m;
	m2 = -m;
	cout << m2;
	
	Matrix2D m3 = m * -1.0;
	cout << m3 + m;

	Vector v3 = m * v1;
	cout << m*v1;

	Vector v4{ 0,1,-1,0 };
	cout << v4 * m;
	return 0;
}