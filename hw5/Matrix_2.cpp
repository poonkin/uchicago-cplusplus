#include "Matrix_2.h"
#include <iostream>
#include <cstdlib>
#include <boost/progress.hpp>
using namespace mpcs51044;
using namespace std;

int main()
{
	boost::progress_timer howlong;
	try {
		Matrix<3, 3> m = { 
				{ 1, 2, 3 }, 
				{ 4, 5, 6 }, 
				{ 7, 8, 9 },
				{ 10, 11, 12 } 
		};
		
		static double total;
		for (int i = 0; i < 10000000; i++) {
			m(1, 1) = i;
			total += m.determinant();
		}
		cout << total << endl;
	}
	catch( std::invalid_argument e )
	{
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	
	/*Matrix<3, 3> m = { 
			{ 1, 2, 3 }, 
			{ 4, 5, 6 }, 
			{ 7, 8, 9 }
	};*/
	//cout << m << endl;
	
}

