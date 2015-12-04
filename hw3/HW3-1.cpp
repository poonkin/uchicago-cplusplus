// HW3-1.cpp

/* 
Michael Blumenshine
MPCS 51044
Homework 3, Problem 1
Due: 29 January 2015
*/

#include <iostream>

/** The sequence of events:
 * First, a Hello_World is declared and its constructor called. Its constructor instantiates
 * ForceInit, and then prints "Hello" JUST AFTER ForceInit's constructor inits cout. In stack
 * fashion, the ForceInit destructor is called first as the program exits, which prints ", ".
 * Finally, the Hello_World destructor is called, which prints "world!" and endl. The end.
 */ 

struct ForceInit {
	ForceInit() { std::ios_base::Init(); }
	~ForceInit() { std::cout << ", "; }
};

struct Hello_World {
	Hello_World() { ForceInit force; std::cout << "Hello"; }
	~Hello_World() { std::cout << "world!" << std::endl; }
};

Hello_World static_hello;

// Super empty main has nothing and returns 0.
int 
main()
{
	return 0;
}
