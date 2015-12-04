#include "Grading.h"
#include<numeric>
using namespace mpcs51044;
using namespace std;

double
Student_info::grade() const
{
	double avg = accumulate(homework.begin(), homework.end(), 0.0) / homework.size();
	return (midterm + final + avg) / 3;
}
