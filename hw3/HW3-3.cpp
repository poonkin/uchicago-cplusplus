// HW3-3.cpp

/* 
Michael Blumenshine
MPCS 51044
Homework 3, Problem 3 Extra Credit
Due: 29 January 2015
*/

/**

Which is better?
 
I would argue that for most purposes, dynamic cast is better. It didn't allow
us to break the polymorphic relationship; indeed the C-pointer allowed us to
do whatever we wanted, which could have resulted in trying to access certain
members that don't exist.

reinterpret_cast would do a bitwise reinterpretation, giving us full access
to the functionality of the other object. This makes reinterpret_cast the
desired choice in this scenario of allowing C-style behavior.

*/

#include <iostream>
#include <cstdlib>
#include <string>

using std::string;
using std::ostream;
using std::cout;
using std::endl;

// While it ended up being unnecessary for the specification requirements
// of this class, I kept the functionality of class B in having a string message
// that it contains. The default constructor gives it a default message,
// while it can also be passed a string for its message. It also
// overloaded the stream insertion operator to print the message
// when the class is sent to the output stream.
class B
{
public:
	B() { this->message = "Default B message"; }
	B(string message) { this->message = message; }
	friend ostream& operator<<(ostream& os, const B& b_obj);
private:
	string message;
};

// When the ostream sees a B, it prints B's message.
ostream& operator<<(ostream& os, const B& b_obj)
{
	os << b_obj.message;
	return os;
}

// As above, I kept the functionality of the class even though it wasn't necessary.
// In addition, class D inherits from class B, meaning that the class should contain
// a message and d_message. It also overloads the extraction operator << to print
// the message when the class is sent to the output stream.
class D : public B
{
public:
	D() { this->d_message = "Default D message"; }
	D(string message) { this->d_message = message; }
	friend ostream& operator<<(ostream& os, const D& d_obj);
private:
	string d_message;
};

// When the ostream sees a D, it prints D's d_message.
ostream& operator<<(ostream& os, const D& d_obj)
{
	os << d_obj.d_message;
	return os;
}

int main()
{
	B* b_obj = new B;
	D* d_obj = new D;

	cout << "Objects B and D were just created." << endl << endl;
	
	cout << "Original pointer value:" << endl;
	cout << b_obj << endl << endl;
	
	cout << "After casting:" << endl;
	//cout << dynamic_cast<D*>(b_obj) << endl;   // this gave error: cannot dynamic_cast 'b_obj' (of type 'class B*') to type 'class D*' (source type is not polymorphic)
	cout << "NOTE: dynamic_cast wisely did not allow us to turn base class into inherited class, see source code" << endl;
	cout << (D*)b_obj << endl << endl;
	
	cout << "Which is better?" << endl << endl
		<< "I would argue that for most purposes, dynamic cast is better. It didn't allow" << endl
		<< "us to break the polymorphic relationship; indeed the C-pointer allowed us to" << endl
		<< "do whatever we wanted, which could have resulted in trying to access certain" << endl
		<< "members that don't exist." << endl << endl
		<< "reinterpret_cast would do a bitwise reinterpretation, giving us full access" << endl
		<< "to the functionality of the other object. This makes reinterpret_cast the" << endl
		<< "desired choice in the scenario of allowing C-style behavior." << endl << endl;

	delete d_obj;
	delete b_obj;
	
	b_obj = NULL;
	d_obj = NULL;

	return EXIT_SUCCESS;
}
