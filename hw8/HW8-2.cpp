// HW8-2.cpp

/* 
Michael Blumenshine
C++
HW 8 Problem 2 
Due: 5 March 2015
*/

#include <iostream>
#include <thread>
#include <cstdlib>
#include "LockFreeStack.h"

/************************************************************************
 * Explanation for this driver											*
 * ===========================											*
 * 																		*
 * This driver exists to prove that the push operation on the stack		*
 * indeed pushes all values it intends to from two different threads	*
 * concurrently. It does so by assigning to both a very large loop		*
 * that will continue to iterate well past the quanta for threads on	*
 * my machine (indeed on most machines as well).						*
 * 																		*
 * It pushes BIG_NUM (see preprocessor macro below) values from 0 to	*
 * BIG_NUM-1 onto the stack twice, one of each value from one of two 	*
 * threads. Therefore, when this operation is complete, there should be	*
 * BIG_NUM+BIG_NUM values on the stack, which, because they follow the	*
 * form (not strictly in this order) 0, 0, 1, 1, ..., BIG_NUM-1, 		*
 * BIG_NUM-1, we can determine that the sum of these values must be		*
 * BIG_NUM*(BIG_NUM-1). (From N(N+1)/2, but here we have double each	*
 * value).																*
 * 																		*
 * So after two threads push the values, another thread pops and sums	*
 * the entire stack. It then checks whether the reduction variable		*
 * test_sum contains the value BIG_NUM*(BIG_NUM-1) or not. If it does,	*
 * then the push method succeeded. If it fails, then it did not succeed.*
 * 																		*
 * Note: as mentioned above, the large value of BIG_NUM was used so that*
 * any processor, even one that schedules threads in a somewhat serial	*
 * fashion, will eventually spill over with another one.				*
 * 																		*
 ************************************************************************/

#define BIG_NUM 10000000

void func1(cspp51044::Stack &s)
{
	unsigned long long test_sum = 0;
	int i;
	for (i = 0; i < 2*BIG_NUM; ++i)
		test_sum += s.pop();
		
	if (test_sum == (unsigned long long)BIG_NUM*(BIG_NUM-1))
		std::cout << "Success!" << std::endl;
	else std::cout << "Failure!" << std::endl;
	
	//std::cout << test_sum << std::endl;
	//std::cout << (unsigned long long)BIG_NUM*(BIG_NUM-1) << std::endl;
}

void func2(cspp51044::Stack &s)
{
	int i;
	for (i = 0; i < BIG_NUM; ++i)
		s.push(i);
}

int main()
{
	cspp51044::Stack s;
	std::thread t1((func2), std::ref(s));
	std::thread t2((func2), std::ref(s));
	
	t1.join();
	t2.join();

	std::thread t3((func1), std::ref(s));
	
	t3.join();

	return EXIT_SUCCESS;
}
