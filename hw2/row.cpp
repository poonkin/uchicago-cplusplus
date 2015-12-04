// row.cpp

/* Michael Blumenshine
 * row implementation file
 * HW2-4 */

#include <vector>
#include <numeric>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "triangle.h"

using namespace std;

const int size = 12;

// A row constructor does nothing. I wrote this thinking that it might have some code.
Row::Row()
{
	
}

// A row destructor clears its elements vector.
Row::~Row()
{
	this->elements.clear();
}

// A getter member function for returning a particular element in a Row's elements vector.
int Row::get_element(int i)
{
	return this->elements[i];
}

// A getter for the size of the Row's elements vector.
size_t Row::get_size()
{
	return this->elements.size();
}

// Enables access to the otherwise private elements vector's push_back function.
void Row::push(int i)
{
	this->elements.push_back(i);
}

// A setter for individual elements, where i is the index in the elements vector and value is
// the value to replace the old value at i.
void Row::set_element(int i, int value)
{
	this->elements[i] = value;
}

// printRow prints a row. It relies on the private member function centeredInt.
void
Row::printRow(int eltSize)
{
    for(size_t i = 0; i < this->elements.size(); ++i) {
        cout << left << setw(eltSize) << centeredInt(this->elements[i], eltSize) << " ";
    }
    cout << endl;
}

// used by printTriangle in the triangle class.
int Row::max_element_row()
{
	int maximum_element = *max_element(this->elements.begin(), this->elements.end());
	return maximum_element;
}

// Private member function for centering a value in a brick.
string
Row::centeredInt(int i, int eltSize)
{
    ostringstream os;
    os << i;
    string str = os.str();
    return string((eltSize - str.size())/2, ' ') + str;
}

