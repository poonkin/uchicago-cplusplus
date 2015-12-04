#ifndef OSTREAM_JOINER_H
#define OSTREAM_JOINER_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <boost/function_output_iterator.hpp>

namespace hw62
{

	template <typename T>
	class ostream_appender
	{
	public:
		ostream_appender(std::string& data, std::string& delim)
		{
			this->app_string = &data;
			this->delim = &delim;
		}
		
		/*void operator()(const T& tostr) const
		{
			std::stringstream ss;
			ss << tostr;
			*(this->app_string) += ss.str();
		} */
		
		std::string* app_string;
		std::string* delim;
	};
	
	template <typename T>
	class ostream_joiner: public std::iterator<std::input_iterator_tag,T,std::ptrdiff_t,const T*,const T&>
	{
	public:
		ostream_joiner<T>(std::ostream& os, std::string delim)
		{
			this->os = &os;
			this->delim = delim;
			this->data = "";
			//boost::make_function_output_iterator(ostream_appender<T>(data, delim));
		}
		
		void operator()(const T& tostr) const
		{
			std::stringstream ss;
			ss << tostr;
			*(this->data) += ss.str();
		} 
		
		~ostream_joiner<T>()
		{
			*(this->os) << *this << std::endl;
		}
		
		ostream_joiner<T> operator ++ (int) { return *(this+1); }
		ostream_joiner<T> operator ++ () { return *(this+1); }
		ostream_joiner<T> operator * () { return *this; }
		void operator= (const T &val) {  }
		
		
		
		inline friend
		std::ostream&
		operator<<
		(std::ostream &os, ostream_joiner<T> ostr) {
			copy(ostr.data.begin(), ostr.data.end()-1-std::distance(ostr.delim.begin(), ostr.delim.end()), std::ostream_iterator<double>(std::cout,""));
			return os;
		}

		std::ostream* os;
		std::string delim;
		std::string data;
	};
	
}

#endif
