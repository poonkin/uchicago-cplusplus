// HW2-2.cpp

/* Michael Blumenshine
 * Homework 2, problem 2
 * MPCS 51044
 * Due: 22 January 2015
 */
 
 // Even vectors: 2 57 92 0 45 8 5 7 29 10		Sorted: 0 2 5 7 8 10 29 45 57 92, median = (8 + 10) / 2 = 9
 // Odd vectors: 2 57 92 0 45 8 5 7 29 10 11    Sorted: 0 2 5 7 8 10 11 29 45 57 92, median = 10
 
 /** Compile with make, although to compile individually, please use:
  * 	g++ -std=c++11 -o HW2-2 HW2-2.cpp
  */
 
 #include <iostream>
 #include <cstdlib>
 #include <algorithm>
 #include <vector>
 #include <iterator>
 #include <climits>
 
 using std::cout;
 using std::endl;
 using std::vector;
 using std::sort;
 using std::partial_sort;
 using std::nth_element;
 
// Function prototypes
void median(vector<int>& v);
void init_pair(vector<int>& v, vector<int>& v2);
double sort_median(vector<int>& v);
double partial_sort_median(vector<int>& v);
double nth_sort_median(vector<int>& v);
void double_init_pair(vector<double>& v, vector<double>& v2);

// EXTRA CREDIT TEMPLATE MEDIAN
// I utilized nth_element for this template
// function as it is the superior method.
// NOTE: MUST BE COMPARABLE, AND DATA TYPE
// MUST SUPPORT ADDITION AND DIVISION FOR THE
// AVERAGE OF TWO MEDIANS EXTRA CREDIT FUNCTIONALITY.
template<typename T>
double template_median(vector<T>& v)
{
	if (v.size() == 0)	// If the size is 0, we don't want to start calculating anything. Distance is 0 (although in truth, it is null).
		return 0.0;
		
	size_t size = v.size();
	
	if (size % 2 == 1)			// Odd number of elements
	{
		nth_element(v.begin(), v.begin()+(size/2), v.end());
		return v[size/2]/1.0;						// Returns the true median.
	}
	else                      		// Even number of elements
	{
		nth_element(v.begin(), v.begin()+(size/2), v.end());
		nth_element(v.begin(), v.begin()+(size/2)-1, v.end());
		
		return (v[size/2] + v[size/2-1])/2.0;		// Returns the average of the two most middle elements.
	}
}

int main()
{
	cout << "HW2.2" << endl << "~~~~~" << endl << endl << "For testing, all vectors are tested with 10 and 11 integers" << endl
	 << "It was done in this way to show that the coded methods work for odd and even vectors" << endl << endl
	 << "The integer list is predetermined and can be found at the beginning of the source code (and below)." << endl
	 << "Even vectors: 2 57 92 0 45 8 5 7 29 10      Sorted: 0 2 5 7 8 10 29 45 57 92, median = (8 + 10) / 2 = 9" << endl
	 << "Odd vectors: 2 57 92 0 45 8 5 7 29 10 11    Sorted: 0 2 5 7 8 10 11 29 45 57 92, median = 10" << endl << endl
	 << "The template array is tested using the double versions of the same values"
	 << endl << "with a few extra decimal values for good measure!" << endl << endl;
	
	// PART 1, USING SORT
	
	// Vectors for median_sort
	vector<int> vsort_even;
	vector<int> vsort_odd;
	
	init_pair(vsort_even, vsort_odd);	// init_pair pushes the values located above onto the vectors.
	
	// Note: the median functions are called in the code below, simply send result to output stream.
	cout << "Median, sorted even: " << sort_median(vsort_even) << endl;
	cout << "Median, sorted odd: " << sort_median(vsort_odd) << endl << endl;
	
	// Vectors for partial_sort
	vector<int> vpartsort_even;
	vector<int> vpartsort_odd;
	
	init_pair(vpartsort_even, vpartsort_odd);
	
	// Note: the median functions are called in the code below, simply send result to output stream.
	cout << "Median, partially sorted even: " << partial_sort_median(vpartsort_even) << endl;
	cout << "Median, partially sorted odd: " << partial_sort_median(vpartsort_odd) << endl << endl;
	
	// Vectors for nth_element
	vector<int> vnth_even;
	vector<int> vnth_odd;
	
	init_pair(vnth_even, vnth_odd);
	
	// Note: the median functions are called in the code below, simply send result to output stream.
	cout << "Median, nth sorted even: " << nth_sort_median(vnth_even) << endl;
	cout << "Median, nth sorted odd: " << nth_sort_median(vnth_odd) << endl << endl;
	
	// Vectors for the nth_element template median function.
	vector<double> template_even;
	vector<double> template_odd;
	
	double_init_pair(template_even, template_odd);
	
	// Note: the median functions are called in the code below, simply send result to output stream.
	cout << "Template (double), nth sorted even: " << template_median(template_even) << endl;
	cout << "Template (double), nth sorted odd: " << template_median(template_odd) << endl << endl;
	
	// Clears found below. Perhaps unnecessary with primitive data types,
	// but I didn't want to risk a memory leak.
	vsort_even.clear();
	vsort_odd.clear();
	
	vpartsort_even.clear();
	vpartsort_odd.clear();
	
	vnth_even.clear();
	vnth_odd.clear();
	
	template_even.clear();
	template_odd.clear();
	
	return EXIT_SUCCESS;
}

// sort_median sorts the entire vector and then calculates its median. It uses
// the STL sort function. If the vector contains an odd number of elements, it
// returns the true median, while if the vector contains an even number of elements,
// it returns the average of the two most middle elements (located at size/2 and size/2-1).
// If the vector contains no elements, then it returns 0.
double sort_median(vector<int>& v)
{
	if (v.size() == 0)
		return 0.0;
	
	sort(v.begin(), v.end());
	
	size_t size = v.size();
	if (size % 2 == 1)			// Odd number of elements
	{
		return v[size/2]/1.0;						// Returns the true median.
	}
	else                      		// Even number of elements
	{
		return (v[size/2] + v[size/2-1])/2.0;		// Returns the average of the two most middle elements.
	}
}

// partial_sort_median sorts the vector up to the median values and then calculates its median. It uses
// the STL partial_sort function. If the vector contains an odd number of elements, it
// returns the true median, while if the vector contains an even number of elements,
// it returns the average of the two most middle elements (located at size/2 and size/2-1).
// If the vector contains no elements, then it returns 0.
double partial_sort_median(vector<int>& v)
{
	if (v.size() == 0)
		return 0.0;
	
	partial_sort(v.begin(), v.begin()+(v.size()/2)+1, v.end());
	
	size_t size = v.size();
	if (size % 2 == 1)			// Odd number of elements
	{
		return v[size/2]/1.0;						// Returns the true median.
	}
	else                      		// Even number of elements
	{
		return (v[size/2] + v[size/2-1])/2.0;		// Returns the average of the two most middle elements.
	}
}

// nth_sort_median retrieves either the proper value (in odd case) or values (in even case) for calculating the median. It uses
// the STL nth_element function to put these values where they would be if the vector was sorted. 
// If the vector contains an odd number of elements, it
// returns the true median, while if the vector contains an even number of elements,
// it returns the average of the two most middle elements (located at size/2 and size/2-1).
// If the vector contains no elements, then it returns 0.
double nth_sort_median(vector<int>& v)
{
	if (v.size() == 0)
		return 0.0;
		
	size_t size = v.size();
	
	if (size % 2 == 1)			// Odd number of elements
	{
		nth_element(v.begin(), v.begin()+(size/2), v.end());
		return v[size/2]/1.0;						// Returns the true median.
	}
	else                      		// Even number of elements
	{
		nth_element(v.begin(), v.begin()+(size/2), v.end());    // The function calculates both values to determine the
		nth_element(v.begin(), v.begin()+(size/2)-1, v.end());	// average of the middle-most elements.
		
		return (v[size/2] + v[size/2-1])/2.0;		// Returns the average of the two most middle elements.
	}
	
}

// A function used for testing the median function, init_pair simply initializes two matrices (one for
// evens and one for odds) to a predetermined test case.
void init_pair(vector<int>& v, vector<int>& v2)
{
	v.push_back(2);
	v2.push_back(2);
	v.push_back(57);
	v2.push_back(57);
	v.push_back(92);
	v2.push_back(92); // Fairly naive initialization method, but hey, I felt like typing.
	v.push_back(0);
	v2.push_back(0);
	v.push_back(45);
	v2.push_back(45);
	v.push_back(8);
	v2.push_back(8);
	v.push_back(5);
	v2.push_back(5);
	v.push_back(7);
	v2.push_back(7);
	v.push_back(29);
	v2.push_back(29);
	v.push_back(10);
	v2.push_back(10);
	//v.push_back(11);
	v2.push_back(11);
}

// I should have just made this a template version.
void double_init_pair(vector<double>& v, vector<double>& v2)
{
	v.push_back(2.25);
	v2.push_back(2.25);
	v.push_back(57.658);
	v2.push_back(57.658);
	v.push_back(92.1);
	v2.push_back(92.1); // Fairly naive initialization method, but hey, I felt like typing.
	v.push_back(0.0);
	v2.push_back(0.0);
	v.push_back(45.01);
	v2.push_back(45.01);
	v.push_back(8.52);
	v2.push_back(8.52);
	v.push_back(5.643);
	v2.push_back(5.643);
	v.push_back(7.86);
	v2.push_back(7.86);
	v.push_back(29.15);
	v2.push_back(29.15);
	v.push_back(10.01);
	v2.push_back(10.01);
	//v.push_back(11);
	v2.push_back(11.11);
}
