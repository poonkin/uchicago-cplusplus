#include "median.h"
#include<random>
#include<vector>
#include<algorithm>
#include<iostream>
#include<boost/progress.hpp>
using namespace std;
using namespace mpcs51044;
uniform_real_distribution<> dist(0, 100);
default_random_engine re;

int main()
{
	vector<double> v(10000000);
	generate(v.begin(), v.end(), []() { return dist(re); });
	vector<double> w(v.begin(), v.end());
	{
		boost::progress_timer pt;
		cout << "Using sort: " << median_sort(v) << endl;
	}
	w.assign(v.begin(), v.end());
	{
		boost::progress_timer pt;
		cout << "Using partial sort: " << median_partial_sort(v) << endl;
	}

	w.assign(v.begin(), v.end());
	{
		boost::progress_timer pt;
		cout << "Using nth_element: " << median_nth_element(v) << endl;
	}

	return 0;
}
