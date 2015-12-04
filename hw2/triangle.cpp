// triangle.cpp

/* Michael Blumenshine
 * Triangle implementation file
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

// The triangle constructor initializes its first Row with 1. All triangles start with 1.
Triangle::Triangle()
{
	Row first_row;
	first_row.push(1);
	this->rows.push_back(first_row);
}

// The triangle destructor calls the destructors of all of its rows (which clear themselves),
// then clears its internal data (the rows vector).
Triangle::~Triangle()
{
	for (size_t i = 0; i < this->rows.size(); ++i)
	{
		this->rows[i].~Row();
	}
	this->rows.clear();
}

// The addRow function accomplishes what the original program did in that it adds the rows
// up to size. Size can be adjusted to add and print more rows.
void Triangle::addRow()
{
	Row result;
	int previous = 0;
	for (size_t i = 0; i < this->rows[this->rows.size()-1].get_size() ; ++i ) {
		result.push(previous + this->rows[this->rows.size()-1].get_element(i));
		previous = this->rows[this->rows.size()-1].get_element(i);
	}
	result.push(previous);
	this->rows.push_back(result);
}

// printTriangle prints the triangle, relying on the max_element_row and printRow public functions of the Row class
// and on the triangle's private numDigits class.
void
Triangle::printTriangle()
{
    Row lastRow = this->rows[size - 1];
    // g++ doesn't like the following code because it defines extra std::max functions
    // It's actually surprising the Visual C++ accepts it
    //
    // int maxElement = accumulate(lastRow.begin(), lastRow.end(), 0, max<int>);
    //
    // use this instead
    int maxElement = lastRow.max_element_row();
    int eltSize = numDigits(maxElement);
    for(int i = 0; i < size; i++) {
        string spaces((size - i - 1) * (eltSize + 1) / 2, ' ');
        cout << spaces;
        this->rows[i].printRow(eltSize);
    }
}

// Calculates the number of digits that a number has, using a low-level, C-style approach.
int
Triangle::numDigits(int i)
{
    int digits = 1;
    while((i/=10) != 0) {
        digits++;
    }
    return digits;
}
