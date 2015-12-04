// row.h

/* Michael Blumenshine
 * Row data structure
 * HW2-4 */

#ifndef ROW_H
#define ROW_H

#include <vector>
#include <numeric>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>

class Row {
public:
	Row();
	int get_element(int i);
	size_t get_size();
	void set_element(int i, int value);
	void push(int i);
	void printRow(int eltSize);
	int max_element_row();
	~Row();
protected:
	std::vector<int> elements;
	std::string centeredInt(int i, int eltSize);
};

#endif
