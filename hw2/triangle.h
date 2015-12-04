// triangle.h

/* Michael Blumenshine
 * Triangle data structure
 * HW2-4 */

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <numeric>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "row.h"

class Triangle {
public:
	Triangle();
	void addRow();
	void printTriangle();
	~Triangle();
protected:
	std::vector<Row> rows;
	int numDigits(int i);
};


#endif
