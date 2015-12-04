#include "Matrix.h"
#include <iostream>
#include <boost/progress.hpp>
using namespace mpcs51044;
using namespace std;

int main()
{
	boost::progress_timer howlong;
	Matrix<3, 3> m = { 
			{ 1, 2, 3 }, 
			{ 4, 5, 6 }, 
			{ 7, 8, 9 } 
	};
	//cout << m << endl;
	static double total;
	for (int i = 0; i < 10000000; i++) {
		m(1, 1) = i;
		total += m.determinant();
	}
	cout << total << endl;
}

// Observed time: 11.93 s
