#ifndef COMPLEXINT_H
#define COMPLEXINT_H
#include <initializer_list>
#include <algorithm>
#include <array>
#include <memory>
#include <numeric>
#include <iostream>
#include <sstream>
#include <iomanip>

using std::initializer_list;
using std::array;
using std::unique_ptr;
using std::max_element;
using std::accumulate;
using std::inner_product;
using std::ostream;
using std::ostringstream;
using std::streamsize;
using std::setw;
using std::endl;


namespace mpcs51044 {


class ComplexInt {
public:
	ComplexInt() {this->r = 0; this->i = 0;}
	ComplexInt(int r, int i) { this->r = r; this->i = i; }
	
	// Implemented as a member as other integers can be easily expressed as complex using complex literal.
	ComplexInt operator+(ComplexInt const &rhs) const {
		ComplexInt temp;
		
		temp.r = this->r + rhs.r;
		temp.i = this->i + rhs.i;
		
		return temp;
	}
	
	ComplexInt& operator=(ComplexInt const &rhs) {
		(*this).r = rhs.r;
		(*this).i = rhs.i;
		
		return *this;
	}
	
	ComplexInt& operator+= (ComplexInt const &rhs) {
		*this = *this + rhs;
		return *this;
	}
	
	ComplexInt operator*(ComplexInt const &rhs) const {
		ComplexInt temp;
		
		temp.r = this->r * rhs.r - (this->i * rhs.i);
		temp.i = this->r * rhs.i + this->i * rhs.r;
		
		return temp;
	}
	
	ComplexInt operator*=(ComplexInt const &rhs) {
		*this = *this * rhs;
		return *this;
	}

// Extra credit included! Should be able to see the original method for the normal credit method! 
	inline friend
		ostream &
		operator<<
		(ostream &os, ComplexInt c) {
			int c_offset;
			int old_width = std::cout.width();
			ostringstream oss;
			if (c.i >= 0)
				oss << c.r << "+" << c.i << "i";
			else
				oss << c.r << c.i << "i";
			c_offset = oss.str().size();
			os << setw(0);
			for (int i = 0; i < old_width - c_offset; ++i)
				os << ' ';
			
				os << oss.str() << setw(old_width);
			
			return os;
	}
	
	// EXTRA CREDIT, NEEDED FOR LITERAL
	inline friend ComplexInt operator+(int r, ComplexInt c)
	{
		c.r += r;
		return c;
	}
	
	// EXTRA CREDIT, NEEDED FOR 4 - 
	inline friend ComplexInt operator-(int r, ComplexInt c)
	{
		c.r += r;
		c.i *= -1;
		return c;
	}
	
	int get_r() const 
	{
		return this->r;
	}
	
	int get_i() const 
	{
		return this->i;
	}
	
	void set_r(int r)
	{
		this->r = r;
	}
	
	void set_i(int i)
	{
		this->i = i;
	}

private:
	int i;
	int r;
};

// EXTRA CREDIT PROBLEM 5, BUT SEE ABOVE!
ComplexInt operator""_i(unsigned long long i)
{
	ComplexInt temp;
	temp.set_r(0);
	temp.set_i((int)i);
	
	return temp;
}


}
#endif
