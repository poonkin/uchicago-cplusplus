README

Michael Blumenshine
HW7

Note: PLEASE use the makefile, although it might need to be edited on a different system
as -pthread was linked. It requires a relatively up to date g++ as it incorporates OpenMP
for its yummy wall time API.

HW7-1 and HW7-2 can be found in respective .cpp files. HW7-2 completed the extra credit
option with the initializer list.
The work for HW7-3 can be found in the Matrix.h file (with some alterations to Matrix.cpp).
HW7-3 utilizes openmp and thus requires -fopenmp compilation flag.
It also performed LU decomposition for the extra credit:

/** Note, for extra credit, LU decomposition was used. A matrix A can be factored into
 * an upper-triangular matrix U and a lower-triangular matrix L. By theorem in Linear
 * Algebra, det A = det U * det L. The algorithm used results in a UT with a main diagonal
 * all equal to 1, so in this case, det A = det L. As you can see from the time charts below,
 * the running time of a matrix determinant by LU decomposition is much better than even a parallel
 * implementation of the naive method. **/
 
 
 *********************************
IMPORTANT: At the top of the Matrix.h header file, there is a macro called _PARALLEL. When this
is defined, the naive determinant calculation will be performed with threads. Comment it out
to run a serial calculation.
***********************************
 
Also regarding HW7-3, preprocessor macros were set to determine the determinants
of which sized matrices would be calculated. It is currently set to calculate
the determinant of a 11x11 matrix. 10x10 and 12x12 were also used for testing.
 
Lastly, the work for HW7-4 can be found in the for_each.cpp source code file.

Comments for the different homework assignments often serve to answer the questions posed
in the HW slides. These answer comments will be found near the top of the source code file,
with the exception of the output for HW7-1, which can be found at the bottom of the HW7-1.cpp
source file.
