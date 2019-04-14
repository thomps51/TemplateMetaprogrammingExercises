#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 14 April 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tmeta::details::to_function

#include "_function_qualifiers.h"

namespace tmeta { namespace details {
   /* @brief
      Metafunction to create a function type from a return type, collection of types, function_qualifiers
      enum, and variadic indicator.

      Given ReturnType, Collector<Args...>, IsNoExcept, returns
      ReturnType (Args...) noexcept(IsNoExcept)
    */
   template <class ReturnType, class Collector, function_qualifiers FunctionType,
      bool is_variadic = false>
   struct to_function;

   template <class ReturnType, class Collector, function_qualifiers FunctionType,
      bool is_variadic = false>
   using to_function_t =
      typename to_function<ReturnType, Collector, FunctionType, is_variadic>::type;
}}

namespace tmeta { namespace details {
   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
#define TMETA_DETAILS_TO_FUNCTION(_enum, _qualifier)                                               \
   template <class ReturnType, template <class...> class Collector, class... Args>                 \
   struct to_function<ReturnType, Collector<Args...>, function_qualifiers::_enum, false>           \
   {                                                                                               \
      using type = ReturnType(Args...) _qualifier;                                                 \
   };

   TMETA_CALL_WITH_FUNCTION_QUALIFIERS_ENUMS_AND_QUALIFIERS(TMETA_DETAILS_TO_FUNCTION);

#undef TMETA_DETAILS_TO_FUNCTION

   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
#define TMETA_DETAILS_TO_FUNCTION(_enum, _qualifier)                                               \
   template <class ReturnType, template <class...> class Collector, class... Args>                 \
   struct to_function<ReturnType, Collector<Args...>, function_qualifiers::_enum, true>            \
   {                                                                                               \
      using type = ReturnType(Args..., ...) _qualifier;                                            \
   };

   TMETA_CALL_WITH_FUNCTION_QUALIFIERS_ENUMS_AND_QUALIFIERS(TMETA_DETAILS_TO_FUNCTION);

#undef TMETA_DETAILS_TO_FUNCTION
}}
