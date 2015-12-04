// btree.h

/* 
Michael Blumenshine
MPCS 51044
Homework 4, Problem 4 Binary Tree Data Structure
Due: 5 February 2015
*/

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstdlib>
#include <utility>

using namespace std;

struct node
{
	int key_value;
	node *left;
	node *right;
};

class btree
{
    public:
        btree();
        ~btree();
        
        btree(btree const & other_tree);
        btree(btree && other_tree);
        
        btree& operator=(const btree&);
        btree& operator=(btree&&);

		node* get_root();
		
        void insert(int key);
        node *search(int key);
        //void destroy_tree();
		void destroy_tree(node *leaf);	// Can also be used to destroy subtrees within a tree; will destroy all descendants of leaf
		
		void print_tree(node *leaf);	// Can also print a subtree
    private:
		void copy(node* other_tree_node);	// Used by the copy constructor.
		//void destroy_tree(node *leaf);	// Can also be used to destroy subtrees within a tree; will destroy all descendants of leaf
        void insert(int key, node *leaf);
        node *search(int key, node *leaf);
        
        void move_operations(node* leaf, node* other_leaf);
        
        node *root;
};

#endif
