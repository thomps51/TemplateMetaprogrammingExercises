#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 14 April 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tmeta::details::is_variadic

#include "_function_qualifiers.h"
#include <type_traits>

namespace tmeta { namespace details {
   template <class T>
   struct is_variadic;

   template <class T>
   inline constexpr bool is_variadic_v = is_variadic<T>::value;
}}

namespace tmeta { namespace details {
   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class T>
   struct is_variadic : std::false_type
   {
   };

   // **********************************************************************************************
   // Notes: Specialize for variadic functions.
   // ----------------------------------------------------------------------------------------------
#define TMETA_DETAILS_IS_VARIADIC(_enum, _qualifier)                                               \
   template <class ReturnType, class... Args>                                                      \
   struct is_variadic<ReturnType(Args..., ...) _qualifier> : std::true_type                        \
   {                                                                                               \
   };
   TMETA_CALL_WITH_FUNCTION_QUALIFIERS_ENUMS_AND_QUALIFIERS(TMETA_DETAILS_IS_VARIADIC);
#undef TMETA_DETAILS_FUNCTION_QUALIFIERS_GETTER
}}
