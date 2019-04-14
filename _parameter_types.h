#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 13 April 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tmeta::details::parameter_types

#include <type_traits>
#include <tsl/type_traits/is_same.h>
#include "_function_qualifiers.h"

namespace tmeta { namespace details {

   template <class... Args>
   struct parameter_types_collection;

   template <class T>
   struct parameter_types;

   template <class T>
   using parameter_types_t = typename parameter_types<T>::type;
}}

namespace tmeta { namespace details {
   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class T>
   struct parameter_types
   {
      static_assert(tsl::is_same_v<std::void_t<T>, int>, "T must be function");
   };

   // **********************************************************************************************
   // Notes: We must specialize for vardiadic types as well as normal types.
   // ----------------------------------------------------------------------------------------------
#define TMETA_DETAILS_PARAMETER_TYPES(_enum, _qualifier)                                           \
   template <class ReturnType, class... Args>                                                      \
   struct parameter_types<ReturnType(Args...) _qualifier>                                          \
   {                                                                                               \
      using type = parameter_types_collection<Args...>;                                            \
   };                                                                                              \
   template <class ReturnType, class... Args>                                                      \
   struct parameter_types<ReturnType(Args..., ...) _qualifier>                                     \
   {                                                                                               \
      using type = parameter_types_collection<Args...>;                                            \
   };

   TMETA_CALL_WITH_FUNCTION_QUALIFIERS_ENUMS_AND_QUALIFIERS(TMETA_DETAILS_PARAMETER_TYPES);
#undef TMETA_DETAILS_PARAMETER_TYPES

}}
