// HW2-3.cpp

/* Michael Blumenshine
 * Homework 2, problem 3 extra credit
 * MPCS 51044
 * Due: 22 January 2015
 */
 
/** Compile with make, although to compile individually, please use:
 * 	g++ -std=c++11 -o HW2-3 HW2-3.cpp
 */
 
#include "optimized_copy.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <type_traits>
#include "optimized_copy.h"
 
#define VECTOR_SIZE 100000000		// Can adjust the vector to be copied here.

using std::vector;
using std::cout;
using std::endl;
 
// Function prototypes
double copy_time(vector<int>& testA, vector<int>& testB);
double optimized_copy_time(vector<int>& testA, vector<int>& testB);
void init_vector(vector<int>& v);
void print_header();

 
int main()
{
	double duration;		// Used for ctime style time recording.
	
	vector<int> testA;
	vector<int> testB;
	vector<int> testC;
	
	print_header();			// Print information regarding the program.
	
	init_vector(testA);		// We initialize vector A with values 0 to VECTOR_SIZE - 1
	
	duration = copy_time(testA, testB);		// We run copy_time, which returns the double duration.
	
	// Printing of information pertaining to the time it takes to copy.
	cout << "Time to copy a vector of size " << VECTOR_SIZE << " with copy: " << duration << " seconds, " << VECTOR_SIZE/duration << " copies per second." << endl << endl;
	
	duration = optimized_copy_time(testA, testC);	// optimized_copy_time returns double duration for opt copy.
	
	// Printing of information pertaining to the time it takes to copy using optimized_copy.
	cout << "Time to copy a vector of size " << VECTOR_SIZE << " with optimized_copy: " << duration << " seconds, " << VECTOR_SIZE/duration << " copies per second." << endl << endl;
 
	// Clearing anyways, perhaps unnecessary.
	testA.clear();
	testB.clear();
	testC.clear();
 
	return EXIT_SUCCESS;
}

// copy_time sets up the appropriate ctime variables for recording the time.
// It then runs and times the copy function, which copies the elements of one
// vector from beginning to end and inserts them using back_inserter into another vector.
// It calculates the time it took to do so and returns it in seconds
// using return (double)(finish-start)/CLOCKS_PER_SEC; where CLOCKS_PER_SEC is a ctime macro for converting ctimes to seconds.
double copy_time(vector<int>& v1, vector<int>& v2)
{
	clock_t start, finish;
	
	start = clock();
	std::copy(v1.begin(), v1.end(), std::back_inserter(v2));
	finish = clock();
	
	return (double)(finish-start)/CLOCKS_PER_SEC;
}

// optimized_copy_time sets up the appropriate ctime variables for recording the time.
// It then runs and times the optimized_copy function, which copies the elements of one
// vector from beginning to end and inserts them using back_inserter into another vector.
// It calculates the time it took to do so and returns it in seconds
// using return (double)(finish-start)/CLOCKS_PER_SEC; where CLOCKS_PER_SEC is a ctime macro for converting ctimes to seconds.
double optimized_copy_time(vector<int>& v1, vector<int>& v2)
{
	clock_t start, finish;
	
	start = clock();
	optimized_copy(v1.begin(), v1.end(), std::back_inserter(v2));
	finish = clock();
	
	return (double)(finish-start)/CLOCKS_PER_SEC;
}
 
// init_vector initializes the argument vector with elements 0 through VECTOR_SIZE - 1, using the push_back behavior of the vector class. 
void init_vector(vector<int>& v)
{
	for (int i = 0; i < VECTOR_SIZE; ++i)
	{
		v.push_back(i);
	}
 }

// print_header simply prints the header. I got points off an assignment for putting too much code in main, so hey! Better play it safe! :) 
void print_header()
{
	cout << "HW2-3 Extra Credit" << endl << endl;
	
	cout << "This program pushes " << VECTOR_SIZE << " elements into a vector" << endl
		<< "and copies them into two different empty vectors using std::back_inserter." << endl
		<< "The first is copied using the C++ copy function, while the other is copied"	<< endl
		<< "using optimized copy." << endl << endl;
}
