// HW6-2.cpp

/*
Michael Blumenshine
MPCS 51044
Homework 6, Problem 2 (Extra Credit)
Due: 19 February 2015
*/

#include <iostream>
#include <cstdlib>
#include "ostream_joiner.hpp"

// Please see ostream_joiner.hpp for the classes that complete this assignment.

using namespace hw62;

int main()
{
	std::vector<double> v_dbl = {1.2, 5.2, 5.1, 7.2, 8.7};
	
	// We call copy with a ostream_joiner with args std::cout and ", "
	std::copy(v_dbl.begin(), v_dbl.end(), ostream_joiner<double>(std::cout,", "));
	
	std::cout << std::endl;

	return EXIT_SUCCESS;
}
