#ifndef OPTIMIZED_COPY_H
#  define OPTIMIZED_COPY_H
#ifdef __GNUG__
#define has_trivial_copy_constructor is_trivially_copy_constructible
#endif
#include <type_traits>
#include <iterator>
#include <cstring>

using std::integral_constant;
using std::true_type;
using std::is_trivially_copy_constructible;

template<typename I1, typename I2, bool b>
I2 copy_imp(I1 first, I1 last, I2 out, integral_constant<bool, b> const &foo)
{
   while(first != last)
   {
      *out = *first;
      ++out;
      ++first;
   }
   return out;
}

template<typename T>
T* copy_imp(T* first, T* last, T* out, true_type const &)
{
   memcpy(out, first, (last-first)*sizeof(T));
   return out+(last-first);
}

template<typename T>
T* copy_imp(T const* first, T const* last, T* out, true_type const &)
{
   memcpy(out, first, (last-first)*sizeof(T));
   return out+(last-first);
}

template<typename I1, typename I2>
inline I2 optimized_copy(I1 first, I1 last, I2 out)
{
   //
   // We can copy with memcpy if T has a trivial assignment operator,
   // and if the iterator arguments are actually pointers (this last
   // requirement we detect with overload resolution):
   //
   typedef typename std::iterator_traits<I1>::value_type value_type;
   return copy_imp(first, last, out, is_trivially_copy_constructible<value_type>());
}


#endif
