#include "OverloadMatrix.h"
#include <boost/progress.hpp>
#include <iostream>
using namespace std;
using namespace mpcs51044;

int main()
{
	boost::progress_timer howlong;
	Matrix<double, 3, 3> m = { 
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

// Observed time: 8.86 s
