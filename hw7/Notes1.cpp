// CPP NOTES

/*

vector<thread> vt;
vt.emplace_back(thrFunc);	// REVIEW THIS, THREADS?

std::runtime_error(msg [literal] ) is a C++ exception

-- every member function of a class secretly gets the this pointer; so with threads, you'll
	need to specify by sending the thread a reference to the function and then the this pointer.
	In a sense, it needs the information from the original partition of memory in a sense, via a pointer
	and the function reference itself.


Look up aliasing!!!!
* 
* 

* Lock ordering
* 
* "deadly embrace", thread 1 locks A, wants B, thread 2 locks B, wants A
* 
* Best practices for using locks
* 1) document the order
* 2) always acquire them consistent with that order







*/

#if 0

#include <iostream>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <cmath>

// hardware concurrency is 8 on laptop
int main()
{
		
	unsigned const hardware_threads = std::thread::hardware_concurrency();
	unsigned const cached = std::min<unsigned>(hardware_threads != 0 ? hardware_threads : 1, 20);
	
	std::cout << cached << std::endl;
	
	return EXIT_SUCCESS;
}	
#endif

#if 1


#endif
