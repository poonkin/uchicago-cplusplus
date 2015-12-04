README.txt

Michael Blumenshine
README for HW2 Problems
MPCS 51044
Due: 22 January 2015

HW2-1

The program incorporates both parts 1 and 2. For part 1, it copies the vector, squaring as it goes.
For part 2, it uses the original vector and uses a custom binary operation in accumulate to both
accumulate and square the elements of the original vector. It then outputs the square root.

HW2-2

The program was accomplished with six vectors, each odd with the same values and each even with the same values.

Even vectors: 2 57 92 0 45 8 5 7 29 10		Sorted: 0 2 5 7 8 10 29 45 57 92, median = (8 + 10) / 2 = 9
Odd vectors: 2 57 92 0 45 8 5 7 29 10 11    Sorted: 0 2 5 7 8 10 11 29 45 57 92, median = 10

The median function can handle either an evenly sized or odd sized vector. In the even that it is evenly sized, it will take
the average of the two most middle elements (.size()/2-1 and .size()/2).

As for performance, it makes sense that the partially sorted array will require less operations than a full sort. It requires less
sorting, and the other values beyond those that would be required for the median are unnecessary. Likewise, nth_element sorting would
require even less sorting; it doesn't concern itself with either the beginning or the end, but simply the elements that it needs to
calculate the median. Therefore, nth_element is fastest, while partial_sort is faster than sort.

The extra credit template median can be found just after the function prototypes, while other median functions are implemented after main.

HW2-3

As I didn't have any programs that could truly benchmark the performance of optimized copy versus copy, I wrote a quick, tiny program that uses copy and optimized_copy
to copy 100000000 integers to the back of two other empty vectors. Interestingly, copy consistently performs better than optimized_copy on
my system (I'm running Ubuntu 14.04 LTS on a Bulldozer [sigh, terrible] AMD 8-core CPU, compiling with g++ version 4.8.2).
The program displays the times it took for both functions and the copies executed per second.

HW2-4

Rather simple class version of Pascal's Triangle code that the professor released on Chalk. Note: both row and triangle are separate data structures,
separate classes. They consist of plenty of functions and members that are public and protected. The row data structure is contained in row.h
and is implemented in row.cpp, while the triangle data structure is defined in triangle.h and implemented in triangle.cpp. It otherwise
has the same functionality as the original program. Make sure to check all source files for grading; the makefile should link properly, but
I wouldn't want to be graded on just the tidbit that's currently in main!

HW2-5
I did this for extra credit. I'm aware it isn't perfect, but I only had 30 minute to do it and
needed to install boost with that time. Hopefully it'll get me at least a few extra credit points!

My method for skipping already printed file names is not perfectly efficient. It gets the job done, though.
I'm sure I could have implemented this better with more time.
