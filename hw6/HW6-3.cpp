// HW6-3.cpp

/*
Michael Blumenshine
MPCS 51044
Homework 6, Problem 3
Due: 19 February 2015
*/

/** COMMENTS PERTAINING TO PERFORMANCE:
 * unordered_set runtimes grow slower than a set; when tested with one
 * file, the times reported were:
 * 
Number of unique entries (counted using a set): 16889
Time required with set: 0.131137

Number of unique entries (counted using an unordered_set): 16889
Time required with unordered_set: 0.0537561
 * 
 * When tested with all,  
Number of unique entries (counted using a set): 33814
Time required with set: 0.34407

Number of unique entries (counted using an unordered_set): 33814
Time required with unordered_set: 0.122894
  * 
  * When tested with only a few words:
Number of unique entries (counted using a set): 3
Time required with set: 0.000155496

Number of unique entries (counted using an unordered_set): 3
Time required with unordered_set: 6.9876e-05
  * 
  * In conclusion, unordered_set is evidently a faster container for
  * this purpose, however its benefit grows with the input size.
*/


#include <iostream>
#include <cstdlib>
#include <fstream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <omp.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/range/iterator_range.hpp>

using namespace std;
using namespace boost;

// Function prototypes
int using_set();
int using_unordered_set();

int main()
{
	double start, finish;	// For times
	
	cout << "This program counts the number of distinct \"words\" (strings) within" << endl
		<< "Caesar\'s Commentaries, Homer\'s Odyssey, Aristotle\'s Categories, and" << endl
		<< "Cato\'s Roman Farm Management." << endl << endl;
		
	cout << "More files can be included by adding them to the docs subdirectory in" << endl
		<< "in the directory that currently contains the program executable." << endl << endl;
	
	cout << "Number of unique entries (counted using a set): ";
	
	start = omp_get_wtime();	// OpenMP, while a parallel computing technology, has some lovely and simply timing methods.
	cout << using_set();
	finish = omp_get_wtime();
	
	cout << endl << "Time required with set: " << finish-start << endl << endl;
	
	cout << "Number of unique entries (counted using an unordered_set): ";
	
	start = omp_get_wtime();
	cout << using_unordered_set();
	finish = omp_get_wtime();
	
	cout << endl << "Time required with unordered_set: " << finish-start << endl << endl;
		
	return EXIT_SUCCESS;
}

int using_set()
{
	filesystem::path p("./docs/");
	std::set<string> direc;
	
	for (auto entry : boost::make_iterator_range(filesystem::directory_iterator(p), {}))
	{
		string temp;
		string path = entry.path().string();
		
		ifstream read(path);
		while (read >> temp)
		{
			direc.insert(temp);
		}
			//read >> temp;			// used for testing just a few values, see performance comments above
			//direc.insert(temp);
		read.close();
	}
	
	return direc.size();
}

int using_unordered_set()
{
	filesystem::path p("./docs/");
	std::unordered_set<string> direc;
	
	for (auto entry : boost::make_iterator_range(filesystem::directory_iterator(p), {}))
	{
		string temp;
		string path = entry.path().string();
		
		ifstream read(path);
		while (read >> temp)
		{
			direc.insert(temp);
		}
			//read >> temp;			// used for testing just a few values, see performance comments above
			//direc.insert(temp);
		read.close();
	}
	
	return direc.size();
}
