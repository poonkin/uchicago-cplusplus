// HW6-4.cpp

/*
Michael Blumenshine
MPCS 51044
Homework 6, Problem 4
Due: 19 February 2015
*/

// Note to self: consider heap version for this? Multimap sufficient? Review

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/range/iterator_range.hpp>

using namespace std;
using namespace boost;

#define NUM_OF_WORDS 20

// Function prototypes
void n_most_occurrences();

int main()
{
	cout << "This program prints the " << NUM_OF_WORDS << " most common words throughout the following works:" << endl
		<< "Caesar\'s Commentaries, Homer\'s Odyssey, Aristotle\'s Categories, and" << endl
		<< "Cato\'s Roman Farm Management." << endl << endl;
		
	cout << "More files can be included by adding them to the docs subdirectory in" << endl
		<< "in the directory that currently contains the program executable." << endl << endl;
	
	cout << "The " << NUM_OF_WORDS << " most common words: " << endl << endl;
	
	n_most_occurrences();
	
	return EXIT_SUCCESS;
}

void n_most_occurrences()
{
	filesystem::path p("./docs/");
	std::map<string, int> direc;
	std::vector<string> vec;
	
	for (auto entry : boost::make_iterator_range(filesystem::directory_iterator(p), {}))
	{
		string temp;
		string path = entry.path().string();
		
		ifstream read(path);
		while (read >> temp)
		{
			vec.push_back(temp);
		}			
		read.close();
	}
	
	for (auto it : vec)
		++direc[it];
				
	multimap<int, string, greater<int> > counter;
		
	transform(direc.begin(), direc.end(), std::inserter(counter, counter.begin()), 
		[] (const std::pair<std::string, int> &pr) 
		{ return std::pair<int, std::string>(pr.second, pr.first); } );

	int count = 0;
	for (auto it = counter.begin(); count < NUM_OF_WORDS && it != counter.end(); ++it, ++count)
		cout << it->second << " \t\t: " << it->first << endl;
}
