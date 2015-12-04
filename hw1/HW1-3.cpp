// HW1-3.cpp

/*
 Michael Blumenshine
 HW 1.3
 MPCS 51044
 Due: January 15, 2015
*/

// Note: this program can format any size (within reason... screen size does matter!) but
// only calculates 8 rows. This was my interpretation of the requirements of the assignment.
// The #define NUM_OF_ROWS just below can be used to adjust the triangle size.
// See output after source code.

#include <vector>
#include <iostream>
#include <cstdlib>
#include <math.h>
#define NUM_OF_ROWS 8	// For easy adjustment of the number of rows calculated.
#define PADDING 3		// For easy adjustment of padding in "bricks".

using namespace std;

int main()
{
	// Index variables.
	unsigned int i, j;	
	// We declare a nested vector with 8 rows and columns initially set to 0 in length.
	// This is simply to play with the push_back command; we can have used this much as
	// a 2D array.
	vector<vector<int> > pascal_triangle(NUM_OF_ROWS,vector<int>(0));
	
	cout << endl << "Pascal's Triangle" << endl << "Note: padding can be adjusted" << endl << endl;
	
	// First we insert the initial 1 at the apex of the triangle.
	pascal_triangle[0].push_back(1);
	
	// The program does not offer the option to
	// specify rows; it only prints 8 as per the
	// assignment requirements.
	for (i = 1; i < NUM_OF_ROWS; ++i)
	{
		// Every row of Pascal's triangle begins with a 1.
		pascal_triangle[i].push_back(1);
		
		// All entries in between the first and the last are determined
		// by adding the [i-1][j-1] and [i-1][j] entries.
		for (j = 1; j < i; ++j)
		{
			pascal_triangle[i].push_back(pascal_triangle[i-1][j-1] + pascal_triangle[i-1][j]);
		}
		
		// Every row ends with a 1.
		pascal_triangle[i].push_back(1);
	}
	
	
	//******  SINCE THIS HOMEWORK SEEMS TO WANT A METHOD FOR FORMATTING TRIANGLE ***//
	// ***           OF ANY SIZE, THE FOLLOWING DOES SO EVEN THOUGH             *** //
	//***** IT WOULD BE TRIVIAL TO ACCOMPLISH IF 8 ROWS WERE ASSUMED THROUGHOUT ****//
	
	unsigned int last_row = pascal_triangle.size() - 1;
	unsigned int last_column = pascal_triangle[last_row].size() - 1;
	int longest_val = pascal_triangle[last_row][last_column/2];
	int digit_count = 1; // Any entry will have at least 1 digit.
	int display_length;
	int cell_length;
	unsigned int k;
	
	// Herein we calculate the digit length of the largest integer of the triangle.
	while ((longest_val /= 10) > 0)
		++digit_count;
		
	// We calculate the display length by adding the padding and length of the largest
	// integer and multiplying both by the size of the last_row.
	cell_length = digit_count + PADDING;
	display_length = cell_length * pascal_triangle[last_row].size();

	// We set it to an odd number length per the suggestion from the HW slide.
	if (display_length % 2 == 0) ++display_length;
	
	for (i = 0; i < NUM_OF_ROWS; ++i)
	{
		j = 0;
		k = 0;
		while (j < pascal_triangle[i].size())
		{	
			// We skip over fractional spaces until we arrive at the spot
			// where we will enter the next value.
			while (k < round(display_length*(j+1)/(i+2)))
			{
				cout << ' ';
				++k;
			}
			++k;
			
			// The following five lines of code are required to keep the format
			// nice in the event that integer values take up more than one
			// digit place. This works with any number of digits.
			longest_val = pascal_triangle[i][j];
			while ((longest_val /= 10) > 0)
			{
				++k;
			}
			
			cout << pascal_triangle[i][j++];
		}
		
		cout << endl;
	}

	return EXIT_SUCCESS;
}
