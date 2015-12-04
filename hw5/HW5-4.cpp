// HW5-4.cpp

/*
Michael Blumenshine
MPCS 51044
Homework 5, Problem 4
Due: 12 February 2015
*/

/** NOTE THAT THIS FILE AND ComplexInt.h ALSO CONTAINS SOLUTIONS TO EXTRA CREDIT PROBLEMS 5 AND 6 **/

#include <iostream>
#include <cstdlib>
#include "ComplexInt.h"

using namespace std;
using namespace mpcs51044;

int main()
{
	ComplexInt c1(2,5);
	ComplexInt c2 = 6 + 3_i;		// EXTRA CREDIT PROBLEM 5
	
	cout << "Tests of the overloaded operators:" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl  << endl;
		
	cout << "c1: " << c1 << endl;
	cout << "c2: " << c2 << endl << endl;
	
	cout << "c1 + c2" << endl << c1 + c2 << endl << endl;
	cout << "c1 * c2" << endl << c1 * c2 << endl << endl;
	
	cout << "Testing *= operator (c1 *= c1 + c2)" << endl;
	c1 *= c1 + c2;
	cout << "Success" << endl << endl;
	
	cout << "Printing contents of c1" << endl;
	cout << c1 << endl << endl;
	
	
	// EXTRA CREDIT PROBLEM 6
	cout << "Printing extra credit problem 6 contents" << endl;
	ComplexInt ci(2,7);
	cout << setw(10) << ci << endl;
	cout << "Take a look in the header file; it calls setw(0) at beginning and setw(10) at end" << endl;
	cout << "creating a tunnel of no width so that the class can be handled as it is supposed to." << endl;

	return EXIT_SUCCESS;
}
