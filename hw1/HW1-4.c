// HW1-4.c

// Michael Blumenshine
// HW 1.4
// MPCS 51044
// Due: January 15, 2015

// For convenience, I've included a C and C++ version of these files.

// The C version compiles successfully but gives many warnings.

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
	char * new = "new";			// new is a reserved keyword in C++ but not in C.
	char * delete = "delete";		// delete is a reserved keyword in C++ but not in C.
	int i;

	int * values = malloc(15 * sizeof(int));		// error: invalid conversion from 'void*' to 'int*'
	
	printf("It took much time, but I knew that %s would cause me to %s my C++ version of this program!\n", new, delete);
	
	for (i = 0; i < 15; ++i)
	{
		values[i] = i;
	}
	
	printf("Here are your %s values:\n", new);
	for (i = 0; i < 15; ++i)
	{
		printf("%d\n", values[i]);
	}

	return EXIT_SUCCESS;
}
