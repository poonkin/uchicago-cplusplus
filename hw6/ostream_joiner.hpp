// ostream_joiner.hpp

#ifndef OSTREAM_JOINER_HPP
#define OSTREAM_JOINER_HPP

/*
Michael Blumenshine
MPCS 51044
Homework 6, Problem 2 (Extra Credit) ostream_joiner class and unary function
Due: 19 February 2015
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <iterator>
#include <sstream>
#include <functional>
#include <ostream>
#include <algorithm>
#include <boost/function_output_iterator.hpp>

namespace hw62
{

// For the unary function descendant ostream_appender which ostream_joiner requires as the work horse.
namespace hw62_utility
{

	template <typename T>
	class ostream_appender : public std::unary_function<const T&, void>		// Much easier if the appender inherits from unary_function.
	{
	public:
		// Default constructor for the appender
		ostream_appender(void)
		{
			this->os = nullptr;
			this->first_entry = true;
		}
	
		// This was tricky; I thought I could use a normal constructor (prior to this assignment, I was a bit confused what explicit
		// even did, but after looking it up, using explicit was beneficial).
		explicit ostream_appender(std::ostream& os, const std::string& delim)
		{
			this->os = &os;
			this->delim = delim;
			this->first_entry = true;
		}
		
		// The operator always prints the delimiter BEFORE the value, which allows for a simple check to see whether
		// the first entry has been printed or not. If it hasn't, it'll skip the delimiter. If it has, it'll print the delimiter
		// and then the value, ending at the last value (thus no last delimiter).
		void operator()(const T& tostr) 
		{
			if (this->first_entry)
				this->first_entry = false;
			else
				*os << delim;
			*os << tostr;
		} 
	private:
		std::ostream* os;		// pointer to ostream
		std::string delim;		// the delimiter
		bool first_entry;		// bool used to check whether the first entry had been operated on or not
	};
} // end hw62_utility namespace
	
// The ostream_joiner inherits from the function_output_iterator for an efficient and optimized implementation.
template <typename T>
class ostream_joiner : public boost::function_output_iterator<hw62_utility::ostream_appender<T> >
{
public:
	// Default constructor
	ostream_joiner(void) {}
	
	// Calls parent constructor with the needed information. The default delimiter is "" for copying without delimiting.	
	explicit ostream_joiner(std::ostream& os, const std::string& delim="") 
		: boost::function_output_iterator<hw62_utility::ostream_appender<T> >(hw62_utility::ostream_appender<T>(os, delim)) {}
		
		
};
	
}	// end of hw62 namespace

#endif
