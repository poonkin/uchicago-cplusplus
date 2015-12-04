// HW3-6.cpp

/* 
Michael Blumenshine
MPCS 51044
Homework 3, Problem 6 Extra Credit
Due: 29 January 2015
*/

#include <cstdlib>

class A
{
public:
	A() { im_gonna_trick_ye(); }		// I needed to use this in order to get it to build.
	virtual void f() = 0;
	void im_gonna_trick_ye() { f(); }	// It hides the pure virtual function, but still calls it on construction.
};

class B : public A
{
public:
	void f() {}		// Empty function, but A's is called in constructor through a second function.
};

int main()
{
	B b;			// Starts A's constructor, causing a call to a pure virtual function.
	
	return EXIT_SUCCESS;
}
