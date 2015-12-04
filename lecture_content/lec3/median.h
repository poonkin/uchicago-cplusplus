#ifndef MEDIAN_H
#  define MEDIAN_H

#include<vector>
#include<algorithm>

namespace mpcs51044 {

inline
double median_sort(std::vector<double> v)
{
	std::sort(v.begin(), v.end());
	return v[v.size()/2];
}

inline
double median_partial_sort(std::vector<double> v)
{
	std::partial_sort(v.begin(), v.begin() + v.size()/2 + 1, v.end());
	return v[v.size()/2];
}

inline
double median_nth_element(std::vector<double> v)
{
	std::nth_element(v.begin(), v.begin() + v.size()/2, v.end());
	return v[v.size()/2];
}

}
#endif
