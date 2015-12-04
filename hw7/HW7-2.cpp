// HW7-2.cpp

#include <thread>
#include <iostream>
#include <vector>
#include <initializer_list>
#include <mutex>
#include <cstdlib>

//#define DEBUG

/** Note, the extra credit option was completed. See the second contstructor for the stack class **/

namespace mpcs51044
{
	// This stack class is thread-safe, utilizing lock_guards of type
	// std::mutex that ensure that even if an exception is thrown,
	// locks will properly unlock.
	template <typename T>
	class stack
	{
	public:
		stack() { this->data = new std::vector<T>(0); }
		
		// The extra credit initializer_list constructor.
		stack(std::initializer_list<T> il) { this->data = new std::vector<T>(il); }
		
		~stack() { this->data->clear(); delete this->data; }
		
		// Push uses lock_guards for RAII control of the mutex mu.
		void push(T value)
		{
			std::lock_guard<std::mutex> guard(mu);
			this->data->push_back(value);
		}
		
		// Pop both pops the top item off the stack and then returns it
		T pop()
		{
			std::lock_guard<std::mutex> guard(mu);
			T temp = this->data->back();
			this->data->pop_back();
			return temp;
		}
		
		// Print stack prints the stack (for testing)
		void print_stack()
		{
			std::lock_guard<std::mutex> guard(mu);
			for (auto elt : *data)
			{
				std::cout << elt << ' ';
			}
			std::cout << std::endl;
		}
	
	private:				
		std::vector<T>* data;
		std::mutex mu;	
	};

}

// Concurrent_test is a simple test that pushes a few values onto the stack
// and then pops a few values off the stack.
void concurrent_test(mpcs51044::stack<int> &s)
{
	for (int i = 0; i < 12; ++i)
	{
		s.push(i);
	}
	
	for (int i = 0; i < 3; ++i)
	{
		s.pop();
	}
}

int main()
{
	mpcs51044::stack<int> s;
	#ifdef DEBUG
	s.push(4);
	s.push(6);
	s.push(2);
	s.print_stack();
	s.pop();
	s.print_stack();
	#endif
	
	std::thread t1((concurrent_test), std::ref(s));		// std::ref is needed here as threads don't allow normal references
	std::thread t2((concurrent_test), std::ref(s));
	std::thread t3((concurrent_test), std::ref(s));
	
	t1.join();
	t2.join();
	t3.join();
	
	// A final test
	s.print_stack();
	
	// EXTRA CREDIT
	mpcs51044::stack<int> s2 = {1, 2, 3, 4, 5, 6};
	s2.print_stack();

	return EXIT_SUCCESS;
}
