#include <iostream>
using std::cout;
using std::endl;

// declarations.
struct A {
	int x_ = 0;
	int y_ = 0;

	virtual int fnvretint() { return 11; }
	int fnpi( int* ) { return 12; }
	int fnvoidparams() { return 13; }
	int fntakingfn( double (*pf)(float &) ) { return pf(3.5f); }
};
struct B : public A {
  int z_ = 0;
};
int myIntReturnFunction() { return 1; }
void myVoidFnTakingVoidFn( void (*)() ) {}
void myVoidFn() {}
char* myPszFn( char*, char* ) { static char szBuf[10] = "hello"; return szBuf; }

double myDoubleReturningFunction(float&) { return 15.5; }

int main()
{
	//
	// first set
	//

	// int*
	int i = 2;
	int* pi = &i;
	cout << pi << endl;

	// int&
	int& i2 = i;
    i = 5;
	cout << i2 << endl;

	// double
	double d = 1.414;
	cout << d << endl;

	// A * (A is any appropriate class).
    B b;
    b.x_ = 2;
	b.y_ = 3;
	A* pa = &b;
	cout << pa << endl;

	// char const *
    char const * psz = "hello";
	cout << psz << endl;

	// const char&
	char const ch = 'x';
	char const & chr = ch;
	cout << chr << endl;

	// long[7]
	long pi7[7] = { 1, 2, 3, 4, 5, 6, 7 };
	cout << pi7 << endl;

	// int**
	int** ppi = &pi;
    cout << ppi << endl;
    cout << **ppi << endl;

	// int*&
	int*& pi2 = pi;
	cout << pi2 << endl;

	// float&
	float flt = 3.14159265;
	float& flt2 = flt;
	cout << flt2 << endl;

	// int (*)()
	// (See http://www.newty.de/fpt/index.html)
	int (*pf)() = myIntReturnFunction;
	cout << pf() << (*pf)() << endl;

	// int (*&)()
	int (*&pfr)() = pf;
	cout << pfr << endl;

	// char *(*)(char *, char *)
	char szBuf[] = "Hello";
	char* (*pfpszfn)(char*, char*) = myPszFn;
	cout << pfpszfn << endl;
	cout << pfpszfn(szBuf,szBuf) << endl;

    pfpszfn = [](char *l, char *r) { return static_cast<char *>("foo"); }
	// 
	// second set
	// 

	// int A::*
	int A::*pmemint = &A::x_;
	int iTestPmemint = a.*pmemint;
	cout << "iTestPmemint: " << iTestPmemint << endl;
	cout << endl;

	// int (A::*)(int *)
	int (A::*pmemfnpi)(int *) = &A::fnpi;
	cout << "pmemfnpi           : " << ((void*)pmemfnpi)            << endl;
	cout << "(a.*pmemfnpi)(&i)  : " << (a.*pmemfnpi)(&i)   << endl;
	cout << "(pa->*pmemfnpi)(&i): " << (pa->*pmemfnpi)(&i) << endl;
	cout << endl;

	// int (A::**)(int *)
	int (A::**ppmemfnpi)(int *) = &pmemfnpi;
	cout << "ppmemfnpi          : " << ppmemfnpi           << endl;
	cout << "(a.**ppmemfnpi)(&i): " << (a.**ppmemfnpi)(&i) << endl;
	cout << endl;

	// int (A::*&)(int *)
	int (A::*&prmemfnpi)(int *) = pmemfnpi;
	cout << "prmemfnpi         : " << prmemfnpi          << endl;
	cout << "(a.*prmemfnpi)(&i): " << (a.*prmemfnpi)(&i) << endl;
	cout << endl;

	// int (A::*)(double (*)(float &))
	int (A::*pweirdmemfn)(double (*)(float &)) = &A::fntakingfn;
	cout << "pweirdmemfn: " << pweirdmemfn << endl;
	cout << (a.*pweirdmemfn)(myDoubleReturningFunction) << endl;
	cout << endl;
	
	// void (*p[10]) (void (*)() );
	void (*pbunchoffntakingfns[10]) (void (*)() ) = { myVoidFnTakingVoidFn, myVoidFnTakingVoidFn }; // don't fill remaining 8.
	cout << pbunchoffntakingfns    << endl;
	cout << pbunchoffntakingfns[0] << endl;
	pbunchoffntakingfns[0](myVoidFn);
    pbunchoffntakingfns[3] = myVoidFnTakingVoidFn;
	cout << endl;

	cout << "Finished second set." << endl;

	return 0;
}

