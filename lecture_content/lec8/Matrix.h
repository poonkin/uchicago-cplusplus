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
#include <vector>
#include <future>
#include  <stdexcept>
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
    static unsigned concurrency() {
      static unsigned const hardware_threads = std::thread::hardware_concurrency();
      static unsigned const cached = std::min<unsigned>(hardware_threads != 0 ? hardware_threads : 2, rows);
      return cached;
    }

    double determinantStep(int i) const {
      return (i % 2 ? -1 : 1)
              * data[i][0]
              * minor(i, 0).determinantSingleThread();
    }

    double partialDeterminant(int start, int end) const {
      double val = 0;
      for (int i = start; i < end; i++) {
        val += determinantStep(i);
      }
      return val;
    }

	double determinant() const {

        unsigned long const block_size = rows / concurrency();
        std::vector<std::future<double> > futures(concurrency() - 1);
        int block_start = 0;

        for (unsigned long i = 0; i<(concurrency() - 1); ++i) {
          int block_end = block_start + block_size;

          futures[i] = std::async(&Matrix<rows, cols>::partialDeterminant,
                                  this, block_start, block_end);
          block_start = block_end;
        }
        return std::accumulate
          (futures.begin(), futures.end(), partialDeterminant(block_start, rows),
           [](double acc, std::future<double> &fut) { return acc + fut.get(); });
	}

    double determinantSingleThread() const {
      double val = 0;
      for (int i = 0; i < rows; i++) {
        val += (i % 2 ? -1 : 1)
          * data[i][0]
          * minor(i, 0).determinantSingleThread();
      }
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

template<>
double
Matrix<1, 1>::determinantSingleThread() const
{
  return data[0][0];
}

template<>
double
Matrix<1, 1>::determinant() const
{
	return determinantSingleThread();
}

double
Matrix<2, 2>::determinantSingleThread() const
{
  return data[0][0] * data[1][1] - data[1][0] * data[0][1];
}

template<>
double
Matrix<2, 2>::determinant() const
{
  return determinantSingleThread();
}

template<int a, int b, int c>
inline Matrix<a,c>
operator*(Matrix<a, b> const &l, Matrix<b, c> const &r)
{
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