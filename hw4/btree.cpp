// btree.cpp

/*
Michael Blumenshine
MPCS 51044
Homework 4, Problem 4 Binary Tree Implementation
Due: 5 February 2015
*/

/* Improvement List
 *	1) It was redundant to have a public method that destroyed the whole tree, and yet a private
 * 		method to destroy from a certain node. Instead, I removed the public no arg version and
 * 		made the private one arg version public. Now, subtrees can be deleted (including the entire
 * 		tree) publicly. Additionally, the destructor simply calls the one-arg version with root as
 * 		the passed argument.
 * 
 *  2) Added copy constructor and assignment operator in addition to move semantics
 */
#include <iostream>
#include <cstdlib>
#include <utility>
#include "btree.h"

using namespace std;

btree::btree()
{
	root=NULL;
}

btree::~btree()
{
	destroy_tree(root);
}

btree::btree(btree const & other_tree)
{
	root = NULL;
	copy(other_tree.root);
	cout << "Copy constructor called" << endl;
}

btree::btree(btree && other_tree)
{
	this->root = move(other_tree.root);
	move_operations(this->root->left, other_tree.root->left);
	move_operations(this->root->right, other_tree.root->right);
	cout << "Move constructor called" << endl;
}
        
btree& btree::operator=(const btree& other_tree)
{
	destroy_tree(this->root);
	copy(other_tree.root);
	cout << "Copy assignment called" << endl;
	return *this;
}

btree& btree::operator=(btree&& other_tree)
{
	cout << "Move assignment called" << endl;
	destroy_tree(this->root);
	this->root = move(other_tree.root);
	
	
	return *this;
}

void btree::move_operations(node* leaf, node* other_leaf)
{
	if (other_leaf != NULL)
	{
		leaf = move(other_leaf);
		move_operations(leaf->left, other_leaf->left);
		move_operations(leaf->right, other_leaf->right);
	}
}

node* btree::get_root()
{
	return this->root;
}

void btree::destroy_tree(node *leaf)
{
	if(leaf!=NULL)
	{
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
		//leaf = NULL;
	}
}

void btree::print_tree(node* leaf)
{
	if (leaf != NULL)
	{
		print_tree(leaf->left);
		cout << leaf->key_value << ' ';
		print_tree(leaf->right); 
	}
}

void btree::copy(node* other_tree_node)
{
	if (other_tree_node != NULL)
	{
		copy(other_tree_node->left);
		insert(other_tree_node->key_value);
		copy(other_tree_node->right); 
	}
}

void btree::insert(int key, node *leaf)
{
	if (key< leaf->key_value)
	{
		if (leaf->left!=NULL)
		insert(key, leaf->left);
		else
		{
			leaf->left=new node;
			leaf->left->key_value=key;
			leaf->left->left=NULL;    //Sets the left child of the child node to null
			leaf->left->right=NULL;   //Sets the right child of the child node to null
		}  
	}
	else if(key >= leaf->key_value)
	{
		if(leaf->right != NULL)
			insert(key, leaf->right);
		else
		{
			leaf->right=new node;
			leaf->right->key_value=key;
			leaf->right->left=NULL;  //Sets the left child of the child node to null
			leaf->right->right=NULL; //Sets the right child of the child node to null
		}
	}
}

node *btree::search(int key, node *leaf)
{
  if(leaf!=NULL)
  {
    if(key==leaf->key_value)
      return leaf;
    if(key<leaf->key_value)
      return search(key, leaf->left);
    else
      return search(key, leaf->right);
  }
  else return NULL;
}

void btree::insert(int key)
{
	if(root!=NULL)
		insert(key, root);
	else
	{
		root=new node;
		root->key_value=key;
		root->left=NULL;
		root->right=NULL;
	}
}

node *btree::search(int key)
{
  return search(key, root);
}
