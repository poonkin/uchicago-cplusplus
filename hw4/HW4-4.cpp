// HW4-4.cpp

/* 
Michael Blumenshine
MPCS 51044
Homework 4, Problem 4 Driver
Due: 29 January 2015
*/

#include <cstdlib>
#include <iostream>
#include <utility>
#include "btree.h"


using namespace std;

int main()
{
//
	btree tree;
	for (int i = 0; i < 10; ++i)
		tree.insert(i);
		
	btree tree2 = move(tree);
//
	cout << "Printing tree" << endl;
	tree.print_tree(tree.get_root());
	cout << endl << "Finished" << endl << endl;
	
	cout << "Printing tree2" << endl;
	tree2.print_tree(tree.get_root());
	cout << endl << "Finished" << endl << endl;
	
	cout << &tree;
	cout << &tree2;
	
	return EXIT_SUCCESS;
}
