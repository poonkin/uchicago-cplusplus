#include "Matrix.h"
#include <ctime>
#include <iostream>
#include <omp.h>
#include <stdexcept>
using namespace mpcs51044;
using namespace std;

/** Note, for extra credit, LU decomposition was used. A matrix A can be factored into
 * an upper-triangular matrix U and a lower-triangular matrix L. By theorem in Linear
 * Algebra, det A = det U * det L. The algorithm used results in a UT with a main diagonal
 * all equal to 1, so in this case, det A = det L. As you can see from the time charts below,
 * the running time of a matrix determinant by LU decomposition is much better than even a parallel
 * implementation of the naive method. **/

/** The times below represent averages of a few trials **/
/** Times:      	   Serial				Parallel										LU
 * 		Size 10			0.683124 seconds	0.176146 seconds	3.8 x speed up				1.6211e-05 seconds
 *		Size 11			7.70392 seconds		1.60651 seconds 	4.75 x speed up				2.5457e-05 seconds
 * 		Size 12			92.643 seconds		19.0191 seconds		4.87 x speed up				5.6889e-05 seconds

	The larger the matrix becomes, the more the initial overhead of thread
	creation is amortized. While my computer only has four cores, we can 
	see a greater than four time speed up considering hyperthreading; as
	particular threads and even OS tasks are held up with memory access
	operations, which are considerable slower than computations of integer
	or floating point values, other threads may continue executing. The downtime
	of one thread can be populated with the execution of another.

 */
int main()
{
	srand(time(NULL));
	double start, stop;
    try {
		//int count = 1;
#if 0
		Matrix<10,10> m1;
		for (int i = 0; i < 10; ++i )
			for (int j = 0; j < 10; ++j)
				m1(i,j) = rand() % 10 + 1;
		start = omp_get_wtime();
		cout << "From naive method: " << m1.determinant() << endl;
		stop = omp_get_wtime();
		cout << stop-start << " seconds" << endl << endl;
		start = omp_get_wtime();
		cout << "From LU method: " << m1.LU_determinant() << endl;
		stop = omp_get_wtime();
		cout << stop-start << " seconds" << endl << endl;
#endif
#if 1
		Matrix<11, 11> m2;
		for (int i = 0; i < 11; ++i)
			for (int j = 0; j < 11; ++j)
				m2(i,j) = rand() % 10 + 1;
		start = omp_get_wtime();
		cout << "From naive method: " << m2.determinant() << endl;
		stop = omp_get_wtime();
		cout << stop-start << " seconds" << endl << endl;
		start = omp_get_wtime();
		cout << "From LU method: " << m2.LU_determinant() << endl;
		stop = omp_get_wtime();
		cout << stop-start << " seconds" << endl << endl;
		
#endif
#if 0
		Matrix<12, 12> m3;
			
		for (int i = 0; i < 12; ++i)
			for (int j = 0; j < 12; ++j)
				m3(i,j) = rand() % 10 + 1;
		start = omp_get_wtime();
		cout << "From naive method: " << m3.determinant() << endl;
		stop = omp_get_wtime();
		cout << stop-start << " seconds" << endl << endl;
		start = omp_get_wtime();
		cout << "From LU method: " << m3.LU_determinant() << endl;
		stop = omp_get_wtime();
		cout << stop-start << " seconds" << endl << endl;
#endif
    } catch (exception const &e) {
      cout << "Exception: " << e.what() << endl;
    }
}
