// HW3-2.cpp

/* 
Michael Blumenshine
MPCS 51044
Homework 3, Problem 1
Due: 29 January 2015
*/

// IT WAS ASSUMED THAT THE OPERATOR WOULD RETURN INTs
// AS THE EXAMPLE CODE FOR THE ASSIGNMENT UTILIZED A VECTOR
// OF INTS. THIS COULD HAVE BEEN IMPLEMENTED RETURNING DOUBLES
// BUT AT POTENTIAL FLOATING POINT PRECISION LOSS.

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

// The Nth_Power class acts as a functor. It is instantiated by
// giving the power that it will raise objects by. The name
// of the instance can hereby be used as a function name, which
// will raise any number to that power. I used an iterative
// method as opposed to a recursive method as there is less overhead.
class Nth_Power
{
public:
	Nth_Power(int power) : power(power) {}		// The constructor takes the power to which the instance raises numbers.
	int operator()(int x)					// If the instance is named var, someone can calculate
	{										// the nth power by typing var(x).
		int y = x;
		
		for (int i = 1; i < power; ++i)
		{
			y *= x;
		}
		
		return y;
	}
private:
	int power;			// The actual power to which it raises numbers is the only logical private field.
	
};

// This code was used from main, with one exception. std:: was added appropriately, and in the call to transform,
// std::ostream_iterator<int>(std::cout, ", ") was missing its first argument in the original code.
int main()
{
	std::vector<int> v = { 1, 2, 3, 4, 5 };
	Nth_Power cube(3);
	std::cout << cube(7) << std::endl; // prints 343
	// print first five cubes
	std::transform(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ", "), cube);

	return EXIT_SUCCESS;
}
