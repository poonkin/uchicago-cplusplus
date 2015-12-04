// HW8-1.cpp

/*
Michael Blumenshine
MPCS 51044
C++
Due: 5 March 2015
*/

/**
	The code was NOT okay. It results in a deadlock as a result of a "deadly embrace" between the
	two threads. The simplest solution (minimal changes to the code) involves simply reordering
	the lock_guards in one and only one of the thread functions. Having the coutMutex lock and
	outpMutex lock in the same order fixes the problem. unique_lock with explicit calls to lock
	and unlock would have also sufficed.
	 
	One could also use std::lock() and then pass adopt_lock as a parameter to the lock_guard<mutex>
	for extra safety.
**/


#include <thread>
#include <mutex>
#include <iostream>
#include <fstream>
using namespace std;
mutex coutMutex;
mutex outpMutex;
ofstream outp("output.txt");  // Open file as ostream

void thrFunc1() {
// These locks need to be placed in the same order lest a deadlock be possible.
	lock_guard<mutex> coutLock(coutMutex);
	lock_guard<mutex> outpLock(outpMutex);
	cout << "thrFunc1 console output" << endl;
	outp << "thrFunc1 file output" << endl;
}

void thrFunc2() {
// These locks need to be placed in the same order lest a deadlock be possible.
	lock_guard<mutex> coutLock(coutMutex);
	lock_guard<mutex> outpLock(outpMutex);
	cout << "thrFunc2 console output" << endl;
	outp << "thrFunc2 file output" << endl;
}

int main() {
	thread t1(thrFunc1);
	thread t2(thrFunc2);
	t1.join();
	t2.join();
}
