// HW7-1.cpp

/*
Michael Blumenshine
MPCS 51044
C++
Due: 26 February 2015
*/

#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>

/** Comments
 * Please see the bottom of this source code file for the output.
 * I was expecting values to be far more mixed (like when using
 * other parallel processing technologies like OpenMP and MPI).
 * With 100 prints, one thread would always complete before
 * another thread started. When tested with 10000000, one thread would
 * complete about 10000 prints, then another would begin from 0, then
 * another. The order was more random, with some slowly getting ahead
 * of other threads, but they still seemed to complete chunks of about
 * 10000 prints before passing the torch.
 */

std::mutex mu;

void concurrent_print(int i)
{
	std::lock_guard<std::mutex> guard(mu);		// Thank goodness for good old RAII.
	std::cout << "Thread " << std::this_thread::get_id() << " has been called " << i+1;
	if (i + 1 == 1)
		std::cout << " time" << std::endl;
	else std::cout << " times" << std::endl;
}

void print_thread()
{
	for (int i = 0; i < 100; ++i)
	{
		concurrent_print(i);
	}
}


int main()
{
	std::thread t1(print_thread);
	std::thread t2(print_thread);
	std::thread t3(print_thread);
	
	t1.join();
	t2.join();
	t3.join();

	return EXIT_SUCCESS;
}

/*
Thread 139969318622976 has been called 1 time
Thread 139969318622976 has been called 2 times
Thread 139969318622976 has been called 3 times
Thread 139969318622976 has been called 4 times
Thread 139969318622976 has been called 5 times
Thread 139969318622976 has been called 6 times
Thread 139969318622976 has been called 7 times
Thread 139969318622976 has been called 8 times
Thread 139969318622976 has been called 9 times
Thread 139969318622976 has been called 10 times
Thread 139969318622976 has been called 11 times
Thread 139969318622976 has been called 12 times
Thread 139969318622976 has been called 13 times
Thread 139969318622976 has been called 14 times
Thread 139969318622976 has been called 15 times
Thread 139969318622976 has been called 16 times
Thread 139969318622976 has been called 17 times
Thread 139969318622976 has been called 18 times
Thread 139969318622976 has been called 19 times
Thread 139969318622976 has been called 20 times
Thread 139969318622976 has been called 21 times
Thread 139969318622976 has been called 22 times
Thread 139969318622976 has been called 23 times
Thread 139969318622976 has been called 24 times
Thread 139969318622976 has been called 25 times
Thread 139969318622976 has been called 26 times
Thread 139969318622976 has been called 27 times
Thread 139969318622976 has been called 28 times
Thread 139969318622976 has been called 29 times
Thread 139969318622976 has been called 30 times
Thread 139969318622976 has been called 31 times
Thread 139969318622976 has been called 32 times
Thread 139969318622976 has been called 33 times
Thread 139969318622976 has been called 34 times
Thread 139969318622976 has been called 35 times
Thread 139969318622976 has been called 36 times
Thread 139969318622976 has been called 37 times
Thread 139969318622976 has been called 38 times
Thread 139969318622976 has been called 39 times
Thread 139969318622976 has been called 40 times
Thread 139969318622976 has been called 41 times
Thread 139969318622976 has been called 42 times
Thread 139969318622976 has been called 43 times
Thread 139969318622976 has been called 44 times
Thread 139969318622976 has been called 45 times
Thread 139969318622976 has been called 46 times
Thread 139969318622976 has been called 47 times
Thread 139969318622976 has been called 48 times
Thread 139969318622976 has been called 49 times
Thread 139969318622976 has been called 50 times
Thread 139969318622976 has been called 51 times
Thread 139969318622976 has been called 52 times
Thread 139969318622976 has been called 53 times
Thread 139969318622976 has been called 54 times
Thread 139969318622976 has been called 55 times
Thread 139969318622976 has been called 56 times
Thread 139969318622976 has been called 57 times
Thread 139969318622976 has been called 58 times
Thread 139969318622976 has been called 59 times
Thread 139969318622976 has been called 60 times
Thread 139969318622976 has been called 61 times
Thread 139969318622976 has been called 62 times
Thread 139969318622976 has been called 63 times
Thread 139969318622976 has been called 64 times
Thread 139969318622976 has been called 65 times
Thread 139969318622976 has been called 66 times
Thread 139969318622976 has been called 67 times
Thread 139969318622976 has been called 68 times
Thread 139969318622976 has been called 69 times
Thread 139969318622976 has been called 70 times
Thread 139969318622976 has been called 71 times
Thread 139969318622976 has been called 72 times
Thread 139969318622976 has been called 73 times
Thread 139969318622976 has been called 74 times
Thread 139969318622976 has been called 75 times
Thread 139969318622976 has been called 76 times
Thread 139969318622976 has been called 77 times
Thread 139969318622976 has been called 78 times
Thread 139969318622976 has been called 79 times
Thread 139969318622976 has been called 80 times
Thread 139969318622976 has been called 81 times
Thread 139969318622976 has been called 82 times
Thread 139969318622976 has been called 83 times
Thread 139969318622976 has been called 84 times
Thread 139969318622976 has been called 85 times
Thread 139969318622976 has been called 86 times
Thread 139969318622976 has been called 87 times
Thread 139969318622976 has been called 88 times
Thread 139969318622976 has been called 89 times
Thread 139969318622976 has been called 90 times
Thread 139969318622976 has been called 91 times
Thread 139969318622976 has been called 92 times
Thread 139969318622976 has been called 93 times
Thread 139969318622976 has been called 94 times
Thread 139969318622976 has been called 95 times
Thread 139969318622976 has been called 96 times
Thread 139969318622976 has been called 97 times
Thread 139969318622976 has been called 98 times
Thread 139969318622976 has been called 99 times
Thread 139969318622976 has been called 100 times
Thread 139969310230272 has been called 1 time
Thread 139969310230272 has been called 2 times
Thread 139969310230272 has been called 3 times
Thread 139969310230272 has been called 4 times
Thread 139969310230272 has been called 5 times
Thread 139969310230272 has been called 6 times
Thread 139969310230272 has been called 7 times
Thread 139969310230272 has been called 8 times
Thread 139969310230272 has been called 9 times
Thread 139969310230272 has been called 10 times
Thread 139969310230272 has been called 11 times
Thread 139969310230272 has been called 12 times
Thread 139969310230272 has been called 13 times
Thread 139969310230272 has been called 14 times
Thread 139969310230272 has been called 15 times
Thread 139969310230272 has been called 16 times
Thread 139969310230272 has been called 17 times
Thread 139969310230272 has been called 18 times
Thread 139969310230272 has been called 19 times
Thread 139969310230272 has been called 20 times
Thread 139969310230272 has been called 21 times
Thread 139969310230272 has been called 22 times
Thread 139969310230272 has been called 23 times
Thread 139969310230272 has been called 24 times
Thread 139969310230272 has been called 25 times
Thread 139969310230272 has been called 26 times
Thread 139969310230272 has been called 27 times
Thread 139969310230272 has been called 28 times
Thread 139969310230272 has been called 29 times
Thread 139969310230272 has been called 30 times
Thread 139969310230272 has been called 31 times
Thread 139969310230272 has been called 32 times
Thread 139969310230272 has been called 33 times
Thread 139969310230272 has been called 34 times
Thread 139969310230272 has been called 35 times
Thread 139969310230272 has been called 36 times
Thread 139969310230272 has been called 37 times
Thread 139969310230272 has been called 38 times
Thread 139969310230272 has been called 39 times
Thread 139969310230272 has been called 40 times
Thread 139969310230272 has been called 41 times
Thread 139969310230272 has been called 42 times
Thread 139969310230272 has been called 43 times
Thread 139969310230272 has been called 44 times
Thread 139969310230272 has been called 45 times
Thread 139969310230272 has been called 46 times
Thread 139969310230272 has been called 47 times
Thread 139969310230272 has been called 48 times
Thread 139969310230272 has been called 49 times
Thread 139969310230272 has been called 50 times
Thread 139969310230272 has been called 51 times
Thread 139969310230272 has been called 52 times
Thread 139969310230272 has been called 53 times
Thread 139969310230272 has been called 54 times
Thread 139969310230272 has been called 55 times
Thread 139969310230272 has been called 56 times
Thread 139969310230272 has been called 57 times
Thread 139969310230272 has been called 58 times
Thread 139969310230272 has been called 59 times
Thread 139969310230272 has been called 60 times
Thread 139969310230272 has been called 61 times
Thread 139969310230272 has been called 62 times
Thread 139969310230272 has been called 63 times
Thread 139969310230272 has been called 64 times
Thread 139969310230272 has been called 65 times
Thread 139969310230272 has been called 66 times
Thread 139969310230272 has been called 67 times
Thread 139969310230272 has been called 68 times
Thread 139969310230272 has been called 69 times
Thread 139969310230272 has been called 70 times
Thread 139969310230272 has been called 71 times
Thread 139969310230272 has been called 72 times
Thread 139969310230272 has been called 73 times
Thread 139969310230272 has been called 74 times
Thread 139969310230272 has been called 75 times
Thread 139969310230272 has been called 76 times
Thread 139969310230272 has been called 77 times
Thread 139969310230272 has been called 78 times
Thread 139969310230272 has been called 79 times
Thread 139969310230272 has been called 80 times
Thread 139969310230272 has been called 81 times
Thread 139969310230272 has been called 82 times
Thread 139969310230272 has been called 83 times
Thread 139969310230272 has been called 84 times
Thread 139969310230272 has been called 85 times
Thread 139969310230272 has been called 86 times
Thread 139969310230272 has been called 87 times
Thread 139969310230272 has been called 88 times
Thread 139969310230272 has been called 89 times
Thread 139969310230272 has been called 90 times
Thread 139969310230272 has been called 91 times
Thread 139969310230272 has been called 92 times
Thread 139969310230272 has been called 93 times
Thread 139969310230272 has been called 94 times
Thread 139969310230272 has been called 95 times
Thread 139969310230272 has been called 96 times
Thread 139969310230272 has been called 97 times
Thread 139969310230272 has been called 98 times
Thread 139969310230272 has been called 99 times
Thread 139969310230272 has been called 100 times
Thread 139969301837568 has been called 1 time
Thread 139969301837568 has been called 2 times
Thread 139969301837568 has been called 3 times
Thread 139969301837568 has been called 4 times
Thread 139969301837568 has been called 5 times
Thread 139969301837568 has been called 6 times
Thread 139969301837568 has been called 7 times
Thread 139969301837568 has been called 8 times
Thread 139969301837568 has been called 9 times
Thread 139969301837568 has been called 10 times
Thread 139969301837568 has been called 11 times
Thread 139969301837568 has been called 12 times
Thread 139969301837568 has been called 13 times
Thread 139969301837568 has been called 14 times
Thread 139969301837568 has been called 15 times
Thread 139969301837568 has been called 16 times
Thread 139969301837568 has been called 17 times
Thread 139969301837568 has been called 18 times
Thread 139969301837568 has been called 19 times
Thread 139969301837568 has been called 20 times
Thread 139969301837568 has been called 21 times
Thread 139969301837568 has been called 22 times
Thread 139969301837568 has been called 23 times
Thread 139969301837568 has been called 24 times
Thread 139969301837568 has been called 25 times
Thread 139969301837568 has been called 26 times
Thread 139969301837568 has been called 27 times
Thread 139969301837568 has been called 28 times
Thread 139969301837568 has been called 29 times
Thread 139969301837568 has been called 30 times
Thread 139969301837568 has been called 31 times
Thread 139969301837568 has been called 32 times
Thread 139969301837568 has been called 33 times
Thread 139969301837568 has been called 34 times
Thread 139969301837568 has been called 35 times
Thread 139969301837568 has been called 36 times
Thread 139969301837568 has been called 37 times
Thread 139969301837568 has been called 38 times
Thread 139969301837568 has been called 39 times
Thread 139969301837568 has been called 40 times
Thread 139969301837568 has been called 41 times
Thread 139969301837568 has been called 42 times
Thread 139969301837568 has been called 43 times
Thread 139969301837568 has been called 44 times
Thread 139969301837568 has been called 45 times
Thread 139969301837568 has been called 46 times
Thread 139969301837568 has been called 47 times
Thread 139969301837568 has been called 48 times
Thread 139969301837568 has been called 49 times
Thread 139969301837568 has been called 50 times
Thread 139969301837568 has been called 51 times
Thread 139969301837568 has been called 52 times
Thread 139969301837568 has been called 53 times
Thread 139969301837568 has been called 54 times
Thread 139969301837568 has been called 55 times
Thread 139969301837568 has been called 56 times
Thread 139969301837568 has been called 57 times
Thread 139969301837568 has been called 58 times
Thread 139969301837568 has been called 59 times
Thread 139969301837568 has been called 60 times
Thread 139969301837568 has been called 61 times
Thread 139969301837568 has been called 62 times
Thread 139969301837568 has been called 63 times
Thread 139969301837568 has been called 64 times
Thread 139969301837568 has been called 65 times
Thread 139969301837568 has been called 66 times
Thread 139969301837568 has been called 67 times
Thread 139969301837568 has been called 68 times
Thread 139969301837568 has been called 69 times
Thread 139969301837568 has been called 70 times
Thread 139969301837568 has been called 71 times
Thread 139969301837568 has been called 72 times
Thread 139969301837568 has been called 73 times
Thread 139969301837568 has been called 74 times
Thread 139969301837568 has been called 75 times
Thread 139969301837568 has been called 76 times
Thread 139969301837568 has been called 77 times
Thread 139969301837568 has been called 78 times
Thread 139969301837568 has been called 79 times
Thread 139969301837568 has been called 80 times
Thread 139969301837568 has been called 81 times
Thread 139969301837568 has been called 82 times
Thread 139969301837568 has been called 83 times
Thread 139969301837568 has been called 84 times
Thread 139969301837568 has been called 85 times
Thread 139969301837568 has been called 86 times
Thread 139969301837568 has been called 87 times
Thread 139969301837568 has been called 88 times
Thread 139969301837568 has been called 89 times
Thread 139969301837568 has been called 90 times
Thread 139969301837568 has been called 91 times
Thread 139969301837568 has been called 92 times
Thread 139969301837568 has been called 93 times
Thread 139969301837568 has been called 94 times
Thread 139969301837568 has been called 95 times
Thread 139969301837568 has been called 96 times
Thread 139969301837568 has been called 97 times
Thread 139969301837568 has been called 98 times
Thread 139969301837568 has been called 99 times
Thread 139969301837568 has been called 100 times
*/
