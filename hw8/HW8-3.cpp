// HW8-3.cpp

/* 
Michael Blumenshine
C++
HW 8 Problem 3 (with extra credit, maybe?) (no pressure, 100% okay if not acceptable as extra credit)
Due: 5 March 2015
*/

/** Each finger can represent a single binary digit (bit). One finger can thus provide 2^1 options (0 and 1).
	The general rule is that where n = the number of fingers, we have 2^n possible options for numbers.
	This gives us 2^10, or 1024, options for possible numbers. Because we start counting in 0 with binary,
	the highest number possible is 2^n-1. Therefore, while we can count 1024 different numbers on our fingers,
	the highest number we can represent in binary in 1023, or 2^10-1. This obviously differs for people
	with fewer than or more than ten fingers. **/
	
/** For (possible) extra credit: I probably cannot count to 31 in 15 seconds (maybe, who knows), but the computer certainly can: **/

#include <iostream>
#include <cstdlib>
#include <omp.h>

int main()
{
	std::cout << std::endl << "This program prints the binary digits from 0 to 31" << std::endl << "with the most significant digit to the right!" << std::endl << std::endl;
	char arr[8];
	int i, j, k;
	double start, finish;
	
	start = omp_get_wtime();
	for (i = 0; i < 32; ++i)
	{
		k = i;
		for (j = 0; j < 8; ++j)
		{
			if (k % 2)
				arr[7-j] = '1';			// Forgive me for not using a more natural and universal method like recursion to solve this!
			else arr[7-j] = '0';
			k /= 2;
		}
		for (j = 0; j < 8; ++j)
			std::cout << arr[j];
		std::cout << std::endl;
	}
	finish = omp_get_wtime();
	std::cout << std::endl << "Time required to count from 0 to 31: " << finish-start << " seconds" << std::endl;

}
