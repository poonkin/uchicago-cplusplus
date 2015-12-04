// HW5-1.cpp

/*
Michael Blumenshine
MPCS 51044
Homework 5, Problem 1
Due: 12 February 2015
*/

#include "Matrix.h"
#include <iostream>

using namespace mpcs51044;
using namespace std;

int main()
{

	Matrix<3, 3> m = { 
			{ 1, 2, 3 }, 
			{ 4, 5, 6 }, 
			{ 7, 8, 9 } 
	};
	cout << m << endl;
	Matrix<3, 3> m2 = {
			{ 1, 2, 3 },
			{ 4, 5, 6 },
			{ 7, 8, 9 }
	};
	cout << m2 << endl;
	cout << m + m2 << endl;
}
