// HW2-1.cpp

/* Michael Blumenshine
 * Homework 2, problem 1 parts 1 and 2
 * MPCS 51044
 * Due: 22 January 2015
 */
 
 /** NOTE, TO COMPLETE PARTS 1 AND 2 IN ONE STEP, I PRINTED THE VECTOR USING
  * TRANSFORM, BUT THEN ACCUMULATED AND TRANSFORMED THE ORIGINAL VECTOR
  * USING THE FOUR ARGUMENT ACCUMULATE. IT IS WITH THIS LATTER METHOD
  * THAT THE SUM IS PRINTED.
  * 
  * Also note that I did the extra credit version of this part.
  */
  
  /** IMPORTANT NOTE: THE FUNCTION process_vectors CONTAINS THE BULK OF PART 1 ******************************************************* < read pls
  *   * WHEREAS print_distance CONTAINS THE BULK OF part 2 and extra credit! */
  
  /** Compile with make, although to compile individually, please use:
  * 	g++ -std=c++11 -o HW2-1 HW2-1.cpp
  */
 
 #include <iostream>
 #include <vector>
 #include <cstdlib>
 #include <algorithm>
 #include <climits>
 #include <iterator>
 #include <random>
 #include <numeric>
 
 #define TRUE 1					// I can't give up my C-style preprocessor definitions, sorry.
 #define FALSE 0				// Their simplicity does something special for me.
 
 #define MIN_DOUBLE 0			// Permissing values are in range [MIN_DOUBLE, MAX_DOUBLE].
 #define MAX_DOUBLE 100000
 
 using std::cin;
 using std::cout;
 using std::endl;
 using std::vector;
 using std::transform;
 
 // This is a template function that checks whether value (of type T) is within the range [min, max].
 // It returns TRUE (1) if it is indeed within the range, and returns FALSE (0) if it is not.
 template<typename T>
 int check_range(T min, T max, T value)
 {
	if (value >= min && value <= max)
		return TRUE;
	else return FALSE;
 }
 
 // Function prototypes
 void print_header();
 void print_menu();
 double rand_double(double min, double max);
 int get_int(int min, int max);
 int get_double(double min, double max);
 double square_dbl(double i) { return i*i; }
 double multiply(double x, double y) { return x + y * y; }
 void fill_vector(vector<double>& v, int num_of_elements);
 void process_vectors(vector<double>& v, vector<double>& v2);
 void print_distance(vector<double>& v);
 
 int main()
 {
	vector<double> v;	// v is the original vector
	vector<double> v2;	// v2 is the vector to be squared using 
	
	print_header();		// Prints program information, up to the prompt for asking how many elements the vector should have.
	
	int num_of_elements = get_int(1, INT_MAX);		// Receives correct input for number of elements.
	
	print_menu();									// Prints a menu as to how the individual elements will be inputted.
	
	fill_vector(v, num_of_elements);				// The fill_vector function inputs the actual choice and then fills the vector
													// according to the user's choice (1 for random, 2 for inputting individual elements).
	process_vectors(v, v2);							// Processes the vectors using transform and copy.
	
	print_distance(v);								// Prints the distance using accumulate and a binary operator (extra credit version).
	
	// Clearing, perhaps unnecessary, but didn't want to risk memory leaks.
	v.clear();
	v2.clear();
	
	return EXIT_SUCCESS;
 }
 
 // The print_header function prints some information about the program, including the current MIN_DOUBLE and MAX_DOUBLE values
 // and generally what the program will be accomplishing.
 void print_header()
 {
	cout << "HW 2.1" << endl;
	cout << "~~~~~~" << endl << endl;

	cout << "This program will accept doubles between " << MIN_DOUBLE << " and " << MAX_DOUBLE << endl
	<< "(these values are preprocessor definitions and can be changed)" << endl
	<< "and will copy all these vectors into a new vector, squaring them" << endl
	<< "in the process!" << endl << endl;
	
	cout << "It will then calculate the distance with only one function call (accumulate with binary operator)!" << endl << endl;
	
	cout << "How long would you like the vector to be? Enter: ";
 }
 
 // The print_menu function prints the menu for how individual elements will be added to the vector.
 // It then prompts the user for a choice.
 void print_menu()
 {
	cout << endl << "Would you like random doubles, or to insert them yourself? Enter either," << endl;
	cout << "1) Random" << endl << "2) I can do it, thank you" << endl << endl;
	
	cout << "Enter here: ";
 }
 
 // rand_double simply returns a random double using functionality from the random header.
 double rand_double(double min, double max)
 {
	std::uniform_real_distribution<double> unif(min, max);
	std::default_random_engine re;
	return unif(re);
 }
 
 // The get_int function simply checks that a valid int was passed (i.e. the user didn't pass a string)
 // and then calls the template function check_range to determine whether it is within the range
 // needed.
 int get_int(int min, int max)
 {	
	int value;
	int valid_input = FALSE;
	
	while (!valid_input)
	{
		//std::cin.ignore(INT_MAX);
		if (cin >> value)
		{
			if (check_range(min, max, value))		// call to template check_range function
				valid_input = TRUE;			// valid int and range
			else cout << "Out of valid range from " << min << " to " << max << "! Please enter again: ";	// valid input but out of range
		}
		else 
		{
			cout << "Invalid! Please enter a valid integer: ";			// printed if user had bad input, no range consideration
		}
		std::cin.clear();					// clear and ignore are used for CRLF input
		std::cin.ignore(INT_MAX, '\n');
	}
	
	return value;
 }
 
 // The get_double function simply checks that a valid double was passed (i.e. the user didn't pass a string)
 // and then calls the template function check_range to determine whether it is within the range
 // needed.
 int get_double(double min, double max)
 {	
	double value;
	int valid_input = FALSE;
	
	while (!valid_input)
	{
		if (cin >> value)
		{
			if (check_range(min, max, value))		// call to template check_range function
				valid_input = TRUE;
			else cout << "Out of valid range from " << min << " to " << max << "! Please enter again: ";	// valid input, but out of range
		}
		else 
		{
			cout << endl << "Invalid! Please enter a valid double: ";		// invalid input, no range consideration
		}
		std::cin.clear();						// clear and ignore are used for CRLF input
		std::cin.ignore(INT_MAX, '\n');
	}
	
	return value;
 }

// The fill_vector function accepts as input the user's choice from the preceding menu (print_menu) and then processes the choice.
// If the choice is 1 (random), then the vector is filled with num_of_elements doubles (num_of_elements is a value the user specified earlier).
// If the choice is 2, then the user is prompted to individually enter each double for the vector. 
void fill_vector(vector<double>& v, int num_of_elements)
{
	int choice = get_int(1,2);
	
	if (choice == 1)	// 1) Random
	{
		for (int i = 0; i < num_of_elements; ++i)
			v.push_back(rand_double(MIN_DOUBLE, MAX_DOUBLE));
	}
	else    // 2) user input
	{
		for (int i = 0; i < num_of_elements; ++i)
		{
			cout << "Enter: ";
			v.push_back(get_double(MIN_DOUBLE, MAX_DOUBLE));
		}
	}
}

// The process_vectors function completes part 1 of the assignment; it takes as arguments two vectors, the first being the original
// vector and the second the vector that will contain the squares. It then prints the new vector of squared values by copying
// the vector to cout using an ostream_iterator. It avoids an additional comma by copying from v2.begin() to v2.end()-1 then calling copy
// again from v2.end()-1 to v2.end(). Perhaps not performant if copy has significant overhead, but seemed okay for the scope of this
// assignment.
void process_vectors(vector<double>& v, vector<double>& v2)
{
		// Note, both methods are used here to perform both parts of the assignment.
		// First, we use transform.
		transform(v.begin(), v.end(), std::back_inserter(v2), square_dbl);
	
		// After using transform, we print the vector using ostream (as was suggested in the slide).
		cout << endl << "Here is the new vector: " << endl;
		copy(v2.begin(), v2.end()-1, std::ostream_iterator<double>(cout,", "));
	
		// While the comma didn't matter in the professor's words, it was bugging me. Perhaps not the best way of getting rid of it
		// but it works.
		copy (v2.end()-1, v2.end(), std::ostream_iterator<double>(cout,"!"));
}

// The print_distance function accomplishes part 2 and extra credit by using one function call to square and accumulate
// the original vector, which is passed as an argument. It utilizes a function multiply (defined by the function prototypes)
// which acts as the binary operator for squaring the values. It then prints the square root of the variable sum, to which
// accumulate returns.
void print_distance(vector<double>& v)
{
	// Easy test using <2, 2, 2, 2> = 16^2, sqrt = 16, tested with other values.
	double sum = std::accumulate(v.begin(), v.end(), 0.0, multiply);
	
	cout << endl << endl << "Part 2" << endl << "The distance of the original vector from the origin is: " << sqrt(sum) << " !" << endl << endl; 
}
