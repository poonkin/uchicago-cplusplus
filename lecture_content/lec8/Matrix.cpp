#include "Matrix.h"
#include <iostream>
#include <stdexcept>
#include <boost/progress.hpp>
using namespace mpcs51044;
using namespace std;
int const iterations = 1000;
int main()
{
    try {
#if 0
      Matrix<5, 5> m = {
          { 5, 2, 0, 0, -2 },
          { 0, 1, 4, 3, 2},
          { 0, 0, 2, 6, 3 },
          { 0, 0, 3, 4, 1 },
          { 0, 0, 0, 0, 2 }
      };
#elif 0
      Matrix<7, 7> m = {
          { 5, 2, 0, 0, -2, 5, 3 },
          { 0, 1, 4, 3, 2, 4, 1 },
          { 0, 0, 2, 6, 3, 6, 6 },
          { 0, 0, 3, 4, 1, 9, 2 },
          { 0, 0, 0, 0, 2, 0, 0 },
          { 0, 0, 3, 4, 1, 1, 5 },
          { 0, 6, 0, 0, 2, 12, 3 }
      };
#else
      Matrix<9, 9> m = {
          { 5, 2, 0, 0, -2, 5, 3, 2, 6 },
          { 0, 1, 4, 3, 2, 4, 1, 7, 13 },
          { 0, 0, 2, 6, 3, 6, 6, 12, 4 },
          { 0, 0, 3, 4, 1, 9, 2, 33, -5 },
          { 0, 0, 0, 0, 2, 0, 0, 1, 1 },
          { 0, 0, 3, 4, 1, 1, 5, -7, -11 },
          { 0, 6, 0, 0, 2, 12, 3, 17, 3 },
          { 5, 21, -3, 4, 1, 1, 5, -7, -11 },
          { 7, 6, 0, 16, 2, 12, 3, 17, 3 }
      };

#endif
      cout << m.determinant() << endl;
      static double total = 0;
      {
        cout << "Single-threaded determinant" << endl;
        boost::progress_timer howlong;
        for (int i = 0; i < iterations; i++) {
          m(1, 1) = i;
          total += m.determinantSingleThread();
        }
      }
      {
        cout << "Parallel determinant" << endl;
        boost::progress_timer howlong;
        for (int i = 0; i < iterations; i++) {
          m(1, 1) = i;
          total += m.determinant();
        }
      }
      cout << total << endl;
    } catch (exception const &e) {
      cout << "Exception: " << e.what() << endl;
    }
}