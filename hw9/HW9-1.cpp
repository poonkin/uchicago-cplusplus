// HW9-1.cpp

/* Michael Blumenshine
 * HW9.1
 * MPCS 51044
 * 12 March 2015 
 */
 
#include <iostream>
#include <cstdlib>
#include <limits>

using namespace std;

class A
{
public:
	A() : num_dogs(0), num_cats_is_private(0) {}
	int hellothisis_funk(int *var) { return *var; }
	int num_dogs;
	int magick(double (*)(float&)) { return EXIT_SUCCESS; }
private:
	int num_cats_is_private;
};

// I used some C code I had from HPC, just to show 
// a nice use of int **. Yes it does use malloc and
// free, but as the assignment isn't about that,
// hopefully you'll forgive me :)
int ** matrix( int n )
{
	int *data = (int *) calloc( n*n, sizeof(int) );
	int **M  = (int **) malloc( n  * sizeof(int*));
	
	for(int i = 0; i < n; i++ )
		M[i] = &data[i*n];

	return M;
}

void matrix_free( int ** M)
{
	free(M[0]);
	free(M);
}

int function() { return EXIT_SUCCESS; }
// This function is kind of nonsense, returns the lesser string (ascii by place of letter)
char * compare_strings(char* lhs, char* rhs)
{
	int i = 0;
	while (lhs[i] != '\0' && rhs[i] != '\0' && lhs[i] == rhs[i])
		++i;
		
	if (lhs[i] == '\0')
		return lhs;
	else if(lhs[i] < rhs[i])
		return lhs;
	else return rhs;
}

void func(void (*func)()) { }

int main()
{
	int * i = new int;
	int & j = *i;
	double never_use_float = 3.1415;
	A * a = new A();
	const char h = 'h'; 
	char pletter = 'p';
	char * pptr = &pletter;
	char const * hptr = &h; // The character can't change, but h can point to a different char/array of chars
	char const & z = *hptr;
	long longarr[7] = {0, 1, 2, 3, 4, 5, 6};
	int ** mtx = matrix(4);
	int *& ireftoptr = i;
	float why_use_float = 3.14;
	float & bad = why_use_float;
	int (*funk_zhen)() = &function;
	funk_zhen();
	int (*&we_all_same_fun_shn)() = funk_zhen;			// While initializing the function pointers wasn't required, I thought I would do it anyways.
	we_all_same_fun_shn();
	char *(*other_comparator)(char*, char*) = compare_strings;
	other_comparator(pptr, pptr);
	int A::*aptr = &A::num_dogs;
	int (A::*funkpoint)(int *) = &A::hellothisis_funk;
	(a->*funkpoint)(i);
	int (A::**doublefunk)(int *) = &funkpoint;
	(a->**doublefunk)(i);
	int (A::*&refertofunk)(int *) = funkpoint;
	(a->*refertofunk)(i);
	int (A::*crazy)(double(*)(float &)) = &A::magick;
	double (*temp)(float &);
	(a->*crazy)(temp);
	void (*p[10]) (void (*)() );
	
	for ( *i = 0; *i < 10; *i = *i + 1)
		p[*i] = &func;

	void (*temp2)();
	for ( *i = 0; *i < 10; *i = *i + 1)
		(*p[*i])(temp2);
	
	delete a;
	matrix_free(mtx);
	delete i;
	
	return EXIT_SUCCESS;
}
