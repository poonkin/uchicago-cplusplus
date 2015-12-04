#include<cmath>
#include<iostream>
using namespace std;

struct Nth_Power {
	Nth_Power(int x) : n(x) {}
	double operator()(double d) {
		return pow(d, n);
	}
private:
	int n;
};

int main()
{
	Nth_Power cube(3);
	for(int i = 1; i < 10; i++) {
		cout << cube(i) << endl;
	}
	return 0;
}
