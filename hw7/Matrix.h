#ifndef MATRIX_H
#  define MATRIX_H
#include <initializer_list>
#include <algorithm>
#include <array>
#include <memory>
#include <numeric>
#include <iostream>
#include <sstream>
#include <iomanip>
#include  <stdexcept>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <vector>
#define _PARALLEL

#undef minor

using std::initializer_list;
using std::array;
using std::unique_ptr;
using std::max_element;
using std::accumulate;
using std::inner_product;
using std::ostream;
using std::ostringstream;
using std::streamsize;
using std::setw;
using std::endl;
using std::invalid_argument;

namespace mpcs51044 {

template<int rows, int cols = rows>
class Matrix {
public:
	Matrix() : data{} {}
	Matrix(initializer_list<initializer_list<double>> init) {
		if (init.size() != rows) {
			throw invalid_argument("Wrong number of rows in initializer");
		}
		auto dp = data.begin();
		for (auto row : init) {
			if (row.size() != cols) {
				throw invalid_argument("Wrong number of columns in initializer");
			}
			std::copy(row.begin(), row.end(), dp->begin());
			dp++;
		}
	}
	double &operator()(int x, int y) {
		return data[x][y];
	}

	double operator()(int x, int y) const {
		return data[x][y];
	}

	inline friend
		ostream &
		operator<<
		(ostream &os, const Matrix<rows, cols> &m) {
		size_t width = m.longestElementSize() + 2;
		os << "[ " << endl;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				os << setw(static_cast<streamsize>(width)) << m(i, j);
			}
			os << endl;
		}
		os << "]" << endl;
		return os;
	}

	Matrix<rows - 1, cols - 1> minor(int r, int c) const {
		Matrix<rows - 1, cols - 1> result;
		for (int i = 0; i < rows; i++) {
			if (i == r) {
				continue;
			}
			for (int j = 0; j < cols; j++) {
				if (j == c) {
					continue;
				}
				result(i < r ? i : i - 1, j < c ? j : j - 1) = data[i][j];
			}
		}
		return result;
	}
	
	#ifdef _PARALLEL
	static void calc_det(const Matrix<rows,cols>* mtx, double* val, int i)
	{
		double temp = 0;
		
		temp += (i % 2 ? -1 : 1)
				* mtx->data[i][0]
				* mtx->minor(i, 0).det_cont();
		std::mutex mu;
		std::lock_guard<std::mutex> guard(mu);		
		*val += temp;
	}
	
	double det_cont() const {
		static_assert(rows == cols, "Can only take determinant of square matrices");
		double val = 0;
		for (int i = 0; i < rows; i++) {
			val += (i % 2 ? -1 : 1)
				* data[i][0]
				* minor(i, 0).det_cont();
		}
		return val;
	}
	#endif
	
	double LU_determinant() const {
		static_assert(rows == cols, "Can only take determinant of square matrices");
		int i = 0, j = 0, k = 0;
		double l[rows][rows];		// Static as smaller matrices are expected, even the runtimes for
		double u[rows][rows];		// larger matrices with this method is unbearable.
		for (i = 0; i < rows; ++i) {
			for (j = 0; j < cols; ++j) {
				if (j < i) {
					l[j][i] = 0;
				}
				else {
					l[j][i] = this->data[j][i];
					for (k = 0; k < i; ++k) {
						l[j][i] = l[j][i] - l[j][k] * u[k][i];
					}
				}
			}
			// While the UT isn't necessarily needed, it is required to continue computing LT in this algorithm.
			for (j = 0; j < cols; ++j) {
				if (j < i)
					u[i][j] = 0;
				else if (i == j) {
					u[i][j] = 1;
				}
				else {
					u[i][j] = this->data[i][j] / l[i][i];
					for (k = 0; k < i; ++k)
					{
						u[i][j] = u[i][j] - l[i][k]*u[k][j]/l[i][i];
					}
				}
			}
		}
		double det_l = 1;
		for (i = 0; i < rows; ++i)
		{
			det_l *= l[i][i];
		}
		return det_l;
	}

	double determinant() const {
		static_assert(rows == cols, "Can only take determinant of square matrices");
		double val = 0;
		#ifdef _PARALLEL
		std::vector <std::thread> tv(0);
		#endif
		for (int i = 0; i < rows; i++) {
			#ifdef _PARALLEL
			tv.push_back(std::thread((&Matrix::calc_det), this, &val, i));
			#endif
			#ifndef _PARALLEL
			val += (i % 2 ? -1 : 1)
				* data[i][0]
				* minor(i, 0).determinant();
			#endif
		}
		#ifdef _PARALLEL
		size_t tv_size = tv.size();
		for (size_t i = 0; i < tv_size; ++i)
		{
			tv.back().join();
			tv.pop_back();
		}
		#endif
		return val;
	}

private:
	static size_t accumulateMax(size_t acc, double d) {
		ostringstream ostr;
		ostr << d;
		return std::max(acc, ostr.str().size());
	}
	static size_t accumulateMaxRow(size_t acc, array<double, cols> row) {
		return std::max(acc, accumulate(row.begin(), row.end(), static_cast<size_t>(0), accumulateMax));
	}
	size_t longestElementSize() const {
		return accumulate(data.begin(), data.end(), 0, accumulateMaxRow);
	}
	array<array<double, cols>, rows> data;
};
#ifdef _PARALLEL
template<>
double
Matrix<1, 1>::det_cont() const
{
	return data[0][0];
}
#else
template<>
double
Matrix<1, 1>::determinant() const
{
	return data[0][0];
}
#endif
#ifdef _PARALLEL
template<>
double
Matrix<2, 2>::det_cont() const
{
	return data[0][0]*data[1][1] - data[1][0]*data[0][1];
}
#else
template<>
double
Matrix<2, 2>::determinant() const
{
	return data[0][0]*data[1][1] - data[1][0]*data[0][1];
}
#endif

template<int a, int b, int c, int d>
inline Matrix<a, d>
operator*(Matrix<a, b> const &l, Matrix<c, d> const &r)
{
	static_assert(b == c, "When multiplying matrices m1*m2, m1 must have the same number of rows as m2 has columns");
	Matrix<a, d> result;
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < d; j++) {
			double total = 0;
			for (int k = 0; k < b; k++)
				total += l(i, k) * r(k, j);
			result(i, j) = total;
		}
	}
    return result;
}

template<int a, int b>
inline Matrix<a, b>
operator+(Matrix<a, b> const &l, Matrix<a, b> const &r)
{
	Matrix<a, b> result;
	for (int i = 0; i < a; i++) {
        for(int j = 0; j < b; j++)
		  result(i, j) = l(i, j) + r(i, j);
	}
    return result;
}

}
#endif
