#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 14 April 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tmeta::details::function_qualifiers and tmeta::details::function_qualifiers_v

#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/rem.hpp>

namespace tmeta { namespace details {
#define TMETA_DETAILS_QUALIFIER_TUPLE                                                              \
   (, const, const volatile, const volatile &, const volatile &&, const &, const &&, volatile,     \
      volatile &, volatile &&, &, &&, noexcept, const noexcept, const volatile noexcept,           \
      const volatile & noexcept, const volatile && noexcept, const & noexcept, const && noexcept,  \
      volatile noexcept, volatile & noexcept, volatile && noexcept, &noexcept, &&noexcept)

   enum function_qualifier_masks
   {
      M_UNQUALIFIED = 0b00000,
      M_CONST       = 0b00001,
      M_VOLATILE    = 0b00010,
      M_LVALUE_REF  = 0b00100,
      M_RVALUE_REF  = 0b01000,
      M_NOEXCEPT    = 0b10000
   };

   // This construction allows simple determination of if a function is const, noexcept or any
   // combination.
   enum class function_qualifiers
   {
      UNQUALIFIED                        = 0,
      CONST                              = M_CONST,
      CONST_VOLATILE                     = M_CONST       | M_VOLATILE,
      CONST_VOLATILE_LVALUE_REF          = M_CONST       | M_VOLATILE     | M_LVALUE_REF,
      CONST_VOLATILE_RVALUE_REF          = M_CONST       | M_VOLATILE     | M_RVALUE_REF,
      CONST_LVALUE_REF                   = M_CONST       | M_LVALUE_REF,
      CONST_RVALUE_REF                   = M_CONST       | M_RVALUE_REF,
      VOLATILE                           = M_VOLATILE,
      VOLATILE_LVALUE_REF                = M_VOLATILE    | M_LVALUE_REF,
      VOLATILE_RVALUE_REF                = M_VOLATILE    | M_RVALUE_REF,
      LVALUE_REF                         = M_LVALUE_REF,
      RVALUE_REF                         = M_RVALUE_REF,
      NOEXCEPT                           = M_NOEXCEPT,
      NOEXCEPT_CONST                     = M_NOEXCEPT    | M_CONST,
      NOEXCEPT_CONST_VOLATILE            = M_NOEXCEPT    | M_CONST       | M_VOLATILE,
      NOEXCEPT_CONST_VOLATILE_LVALUE_REF = M_NOEXCEPT    | M_CONST   | M_VOLATILE | M_LVALUE_REF,
      NOEXCEPT_CONST_VOLATILE_RVALUE_REF = M_NOEXCEPT    | M_CONST   | M_VOLATILE | M_RVALUE_REF,
      NOEXCEPT_CONST_LVALUE_REF          = M_NOEXCEPT    | M_CONST       | M_LVALUE_REF,
      NOEXCEPT_CONST_RVALUE_REF          = M_NOEXCEPT    | M_CONST       | M_RVALUE_REF,
      NOEXCEPT_VOLATILE                  = M_NOEXCEPT    | M_VOLATILE,
      NOEXCEPT_VOLATILE_LVALUE_REF       = M_NOEXCEPT    | M_VOLATILE     | M_LVALUE_REF,
      NOEXCEPT_VOLATILE_RVALUE_REF       = M_NOEXCEPT    | M_VOLATILE     | M_RVALUE_REF,
      NOEXCEPT_LVALUE_REF                = M_NOEXCEPT    | M_LVALUE_REF,
      NOEXCEPT_RVALUE_REF                = M_NOEXCEPT    | M_RVALUE_REF
   };

#define TMETA_DETAILS_ENUM_TYPE_TUPLE                                                              \
   (UNQUALIFIED, CONST, CONST_VOLATILE, CONST_VOLATILE_LVALUE_REF, CONST_VOLATILE_RVALUE_REF,      \
      CONST_LVALUE_REF, CONST_RVALUE_REF, VOLATILE, VOLATILE_LVALUE_REF, VOLATILE_RVALUE_REF,      \
      LVALUE_REF, RVALUE_REF, NOEXCEPT, NOEXCEPT_CONST, NOEXCEPT_CONST_VOLATILE,                   \
      NOEXCEPT_CONST_VOLATILE_LVALUE_REF, NOEXCEPT_CONST_VOLATILE_RVALUE_REF,                      \
      NOEXCEPT_CONST_LVALUE_REF, NOEXCEPT_CONST_RVALUE_REF, NOEXCEPT_VOLATILE,                     \
      NOEXCEPT_VOLATILE_LVALUE_REF, NOEXCEPT_VOLATILE_RVALUE_REF, NOEXCEPT_LVALUE_REF,             \
      NOEXCEPT_RVALUE_REF)
   //enum class function_qualifiers {
   //   BOOST_PP_TUPLE_REM_CTOR(TMETA_DETAILS_ENUM_TYPE_TUPLE)
   //};

#define TMETA_GET_FUNCTION_QUALIFIERS_ENUM(_elem)                                                  \
   BOOST_PP_TUPLE_ELEM(_elem, TMETA_DETAILS_ENUM_TYPE_TUPLE)

#define TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(_elem)                                             \
   BOOST_PP_TUPLE_ELEM(_elem, TMETA_DETAILS_QUALIFIER_TUPLE)

   // This could probably be done nicer with BOOST_PP_FOR
#define TMETA_CALL_WITH_FUNCTION_QUALIFIERS_ENUMS_AND_QUALIFIERS(_macro)                           \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(0), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(0));      \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(1), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(1));      \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(2), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(2));      \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(3), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(3));      \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(4), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(4));      \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(5), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(5));      \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(6), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(6));      \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(7), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(7));      \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(8), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(8));      \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(9), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(9));      \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(10), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(10));    \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(11), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(11));    \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(12), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(12));    \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(13), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(13));    \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(14), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(14));    \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(15), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(15));    \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(16), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(16));    \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(17), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(17));    \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(18), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(18));    \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(19), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(19));    \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(20), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(20));    \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(21), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(21));    \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(22), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(22));    \
   _macro(TMETA_GET_FUNCTION_QUALIFIERS_ENUM(23), TMETA_GET_FUNCTION_QUALIFIERS_QUALIFIER(23));

   template <class T>
   struct function_qualifiers_getter;

   template <class T>
   inline constexpr function_qualifiers function_qualifiers_v = function_qualifiers_getter<T>::value;
}}

namespace tmeta { namespace details {
   // **********************************************************************************************
   // Notes: We need specializations for normal and variadic function types.
   // ----------------------------------------------------------------------------------------------
#define TMETA_DETAILS_FUNCTION_QUALIFIERS_GETTER(_enum, _qualifier)                                \
   template <class ReturnType, class... Args>                                                      \
   struct function_qualifiers_getter<ReturnType(Args...) _qualifier>                               \
   {                                                                                               \
      static function_qualifiers const value = function_qualifiers::_enum;                         \
   };                                                                                              \
   template <class ReturnType, class... Args>                                                      \
   struct function_qualifiers_getter<ReturnType(Args..., ...) _qualifier>                          \
   {                                                                                               \
      static function_qualifiers const value = function_qualifiers::_enum;                         \
   };
   TMETA_CALL_WITH_FUNCTION_QUALIFIERS_ENUMS_AND_QUALIFIERS(TMETA_DETAILS_FUNCTION_QUALIFIERS_GETTER);
#undef TMETA_DETAILS_FUNCTION_QUALIFIERS_GETTER
}
}
