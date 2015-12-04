#include<thread>
#include<mutex>
#include<iostream>
#include<fstream>
using namespace std;
mutex coutMutex;
mutex outpMutex;
ofstream outp("output.txt"); // Open file as ostream

void thrFunc1() {
	lock_guard<mutex> coutLock(coutMutex);
	lock_guard<mutex> outpLock(outpMutex);
	cout << "thrFunc1 console output" << endl;
	outp << "thrFunc1 file output" << endl;
}

void thrFunc2() {
	lock_guard<mutex> coutLock(coutMutex); // Acquire in correct order
	lock_guard<mutex> outpLock(outpMutex);
	cout << "thrFunc1 console output" << endl;
	outp << "thrFunc1 file output" << endl;
}

void thrFunc2_alternate_solution() {
  lock(coutMutex, outpMutex); // Let lock figure out order for you
  lock_guard<mutex> outpLock(outpMutex, adopt_lock);
  lock_guard<mutex> coutLock(coutMutex, adopt_lock);
  cout << "thrFunc2 console output" << endl;
  outp << "thrFunc2 file output" << endl;
}

int main() {
  thread t1(thrFunc1);
  thread t2(thrFunc2);
  t1.join();
  t2.join();
}
