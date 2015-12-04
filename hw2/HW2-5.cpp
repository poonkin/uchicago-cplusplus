// HW2-5.cpp

/* Michael Blumenshine
 * Homework 2, problem 5 tree file
 * MPCS 51044
 * Due: 22 January 2015
 */

/** Please read:
 * To use this, please type in find DIR | xargs ./HW2-5 . With my bash, simply typing HW2-5 does not work.
 * Compile with make, although to compile individually, please use:
 * g++ -std=c++11 -o HW2-5 HW2-5.cpp
 * 
 I did this for extra credit. I'm aware it isn't perfect, but I only had 30 minute to do it and
 needed to install boost with that time. Hopefully it'll get me at least a few extra credit points!

 My method for skipping already printed file names and directories is not perfectly efficient. It gets the job done, though.
 I'm sure I could have implemented this better with more time.
*/ 
 
#include <iostream>
#include <boost/tokenizer.hpp>	// For boost's tokenizer.
#include <string>
#include <cstdlib>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using boost::tokenizer;

// A Dir_tree class, which consists of a contructor, destructor, and print_tree method as public, while
// its already added words are private.
class Dir_tree {
public:
	Dir_tree();
	~Dir_tree();
	void print_tree(char * c);

private:
	vector<string> added_words;
};


int main(int argc, char ** argv)
{
	Dir_tree directory;
	
	for (int i = 1; i < argc; ++i)
	{
		directory.print_tree(argv[i]);
	}
	
	/* Non-class version follows:
	vector<string> added_words;
	//bool test = false;
	
	for (int i = 1; i < argc; ++i)
	{
		bool test = false;
		int j = 0;
		string s = argv[i];
		boost::char_separator<char> sep("/");
		tokenizer< boost::char_separator<char> > tok(s, sep);
		for (tokenizer< boost::char_separator<char> >::iterator beg=tok.begin(); beg!=tok.end(); ++beg)
		{
			for (int k = 0; k < j; ++k)
				cout << '\t';
			++j;
			test = false;
			for (auto elt : added_words)
			{
				if (elt == *beg)
				{
					test = true;
					break;
				}
			}
			if (!test)
			{
				cout << *beg << endl;
				added_words.push_back(*beg);
			}
		}
	}
	*/

	return EXIT_SUCCESS;
}


// Empty, default constructor.
Dir_tree::Dir_tree()
{
	
}

// The destructor clears the added_words vector.
Dir_tree::~Dir_tree()
{
	this->added_words.clear();
}

// Print tree does the bulk of the work. It uses the boost tokenizer, aided by boost's char_separator and appropriate iterators.
// It looks through all the tokens, checking whether each one has already been printed or not. It only prints
// tokens the first time it finds them. Additionally, it increments one tab for each token, simulating the tree structure.
void Dir_tree::print_tree(char * c)
{
	bool test = false;
	int j = 0;
	string s = c;
	boost::char_separator<char> sep("/");
	tokenizer< boost::char_separator<char> > tok(s, sep);
	for (tokenizer< boost::char_separator<char> >::iterator beg=tok.begin(); beg!=tok.end(); ++beg)
	{
		for (int k = 0; k < j; ++k)
			cout << '\t';
		++j;
		test = false;
		for (auto elt : added_words)
		{
			if (elt == *beg)
			{
				test = true;
				break;
			}
		}
		if (!test)
		{
			cout << *beg << endl;
			added_words.push_back(*beg);
		}
	}
}
