#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 03 February 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tmeta::type_descriptor (problem 2-3 / 2-4)

#include <ostream>

#define USE_TYPE_TRAITS

namespace tmeta
{
   template <class T>
   struct type_descriptor;
}

namespace tmeta { namespace details {
   template <class T>
   struct type_name;
}}

template <class T>
struct tmeta::type_descriptor
{
};

#define TMETA_REGISTER_TYPE(_type)                                                                 \
   template <>                                                                                     \
   struct tmeta::details::type_name<_type>                                                       \
   {                                                                                               \
      constexpr static char const * name = #_type;                                                 \
   };

TMETA_REGISTER_TYPE(char);
TMETA_REGISTER_TYPE(short int);
TMETA_REGISTER_TYPE(int);
TMETA_REGISTER_TYPE(long int);
// etc...

#ifdef USE_TYPE_TRAITS
// I realize if constexpr didn't exist when the book came out, but lets use it here!
template <class T>
std::ostream &
operator<<(std::ostream & os, const ::tmeta::type_descriptor<T> &)
{
   if constexpr (std::is_const_v<T>)
   {
      os << ::tmeta::type_descriptor<std::remove_const_t<T>>() << " const";
   }
   else if constexpr (std::is_pointer_v<T>)
   {
      os << ::tmeta::type_descriptor<std::remove_pointer_t<T>>() << " *";
   }
   else if constexpr (std::is_lvalue_reference_v<T>)
   {
      os << ::tmeta::type_descriptor<std::remove_reference_t<T>>() << " &";
   }
   else if constexpr (std::is_rvalue_reference_v<T>)
   {
      os << ::tmeta::type_descriptor<std::remove_reference_t<T>>() << " &";
   }
   else
   {
      os << ::tmeta::details::type_name<T>::name;
   }
   return os;
}

#else
template <class T>
std::ostream &
operator<<(std::ostream & os, const ::tmeta::type_descriptor<T> & dt)
{
   os << ::tmeta::details::type_name<T>::name;
   return os;
}

#define TMETA_REGISTER_QUALIFIER(_qualifier)                                                       \
   template <class U>                                                                              \
   std::ostream & operator<<(std::ostream & os, const ::tmeta::type_descriptor<U _qualifier> &)    \
   {                                                                                               \
      os << ::tmeta::type_descriptor<U>() << " " #_qualifier;                                      \
      return os;                                                                                   \
   }

TMETA_REGISTER_QUALIFIER(const);
TMETA_REGISTER_QUALIFIER(*);
TMETA_REGISTER_QUALIFIER(&);
TMETA_REGISTER_QUALIFIER(volatile);
TMETA_REGISTER_QUALIFIER(const volatile);
#endif
