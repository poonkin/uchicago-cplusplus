#ifndef MATRIX_H
#  define MATRIX_H
#include <initializer_list>
#include <algorithm>
using std::initializer_list;

namespace mpcs51044 {

template<int rows, int cols>
class Matrix {
public:
	Matrix(initializer_list<initializer_list<double>> init) {
		double(*dp)[cols] = data;
		for (auto row : init) {
			std::copy(row.begin(), row.end(), *dp);
			dp++;
		}
	}
private:
	double data[rows][cols];
};
}
#endif