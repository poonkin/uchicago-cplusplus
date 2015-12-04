// HW2-4.cpp

/* Michael Blumenshine
 * Homework 2, problem 4 Modification of Pascal.cpp
 * MPCS 51044
 * Due: 22 January 2015
 */
 
 /** NOTE:
  * 	Triangle and Row are considered two separate classes. They are defined in triangle.h and row.h and implemented
  * 	in triangle.cpp and row.cpp
  * 
  * 	To compile, type make (proper makefile is working), although you could also use:
  * 	g++ -std=c++11 -o HW2-4 HW2-4.cpp triangle.cpp row.cpp
  */

#include <vector>
#include <numeric>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "triangle.h"
#include "row.h"

using namespace std;

const int size = 12;

int
main()
{
    Triangle triangle;			// instantiate triangle
    
    for(int i = 1; i < size; i++) {
        triangle.addRow();				// call triangle's addRow() member function from 1 to size-1
    }									// NOTE: Triangle's constructor adds the first row in my implementation.
    triangle.printTriangle();			// Call triangle's printTriangle() member function.
    return 0;
}
