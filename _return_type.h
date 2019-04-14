#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 13 April 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tmeta::details::return_type

#include "_function_qualifiers.h"

namespace tmeta { namespace details {
   template <class T>
   struct return_type;

   template <class T>
   using return_type_t = typename return_type<T>::type;
}}

namespace tmeta { namespace details {
   // **********************************************************************************************
   // Notes: Must also specialize for variadic functions.
   // ----------------------------------------------------------------------------------------------
#define TMETA_DETAILS_RETURN_TYPE(_enum, _qualifier)                                               \
   template <class ReturnType, class... Args>                                                      \
   struct return_type<ReturnType(Args...) _qualifier>                                              \
   {                                                                                               \
      using type = ReturnType;                                                                     \
   };                                                                                              \
   template <class ReturnType, class... Args>                                                      \
   struct return_type<ReturnType(Args..., ...) _qualifier>                                           \
   {                                                                                               \
      using type = ReturnType;                                                                     \
   };

   TMETA_CALL_WITH_FUNCTION_QUALIFIERS_ENUMS_AND_QUALIFIERS(TMETA_DETAILS_RETURN_TYPE);
#undef TMETA_DETAILS_RETURN_TYPE
}}
