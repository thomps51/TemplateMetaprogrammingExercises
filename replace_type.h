#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 21 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tmeta::replace_type (Exercise 2-1)

#include <tsl/type_traits/conditional.h>
#include <type_traits>

namespace tmeta {
   /* @brief
      Metafunction that replaces all occurences of X within C with Y.

      While the provided examples are relatively simple, generalizing this is quite hard.  The book
      was also written well before C++11 and variadic templates, which greatly expand our
      generalizing power.  For instance, imagine the following variable:

      @code
      volatile int const * const MyVar[5][4][7];
      @endcode

      Which has a type <code>volatile int const * [5][4][7]</code>, and we want to replace int with
      long, or worse, int const * [5] with long * [10].

      Here we can have an arbitrary number of pointer levels and array levels, since
      <code>const volatile int* const***volatile**** [5][4][7][3][6][11]</code> is a perfectly valid
      type according to the compiler.

      Arrays are special in their own right: unlike the other qualifiers, arrays go from right to
      left in importance.  In the above example, pointer is the top level type of the non array
      piece and [5] is the top level type of the array.  This leads to complications when trying to
      substitute something such as C = int * [1][2] with X = int * [1] Y = long * [1], as removing
      the arrays as you would other types leads goes from:

      int * [1][2]  // one pair of two elements
      int * [2] // two elements
      int * // base element

      So the substitution would never fire since int * [1] is never matched.  This is desired, but
      unclear behavior.  The type int * [1] only appears in our english reading of the type, but not
      the actual type: there is no array of 1 element in int * [1][2].

      More explicitly:
      int * [1][2] : {{a,b}}
      int * [2] : {a, b}
      int * : a
      int * [1] : {a}

      In the builtin-type arena, there's also functions, function pointers, and member function
      pointers, which can have an arbitrarily large number of arguments.

      That's just one dimension as well, there's also deeply nested template types (think
      std::vector<std::vector<int>>, which is really
      std::vector<std::vector<int, std::allocator<int>>, std::allocator<std::vector<int>) and
      arbritrarily many template parameters.

      I assert that ALL of these strange cases, even if combined will work properly with this
      implementation.

      ::value is set to true if the replacement was successful, false if not successful.  ::type
      will be equal to C if replacement was not successful.
   */
   template <class C, class X, class Y>
   struct replace_type;

   template <class C, class X, class Y>
   using replace_type_t = typename replace_type<C, X, Y>::type; 
}

namespace tmeta { namespace details {
   /* @brief
      Data structure to store types in.
    */
   template <class...>
   struct collector;
   
   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class C, class X, class Y, class = void>
   struct cv_helper
   {
      using type = const volatile replace_type_t<C, X, Y>;
   };
   
   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class C, class X, class Y>
   struct cv_helper<C, X, Y, std::enable_if_t<tsl::is_same_v<X,  volatile C>>>
   {
      using type = const Y;
   };
   
   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class C, class X, class Y>
   struct cv_helper<C, X, Y, std::enable_if_t<tsl::is_same_v<X,  const C>>>
   {
      using type = volatile Y;
   };

   // **********************************************************************************************
   // Notes: Takes a templated class T and replaces the outer template with U.
   // E.g. : T<Args....> -> U<Args...>
   // Usually used with a collector class: i.e. collect all the types you want, then substitute
   // the collector class with the desired type.  This can be used to recursively construct types
   // that otherwise wouldn't be valid at every level.
   // ----------------------------------------------------------------------------------------------
   template <class T, template <class...> class U>
   struct substitute;
   
   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class T, template <class...> class U>
   using substitute_t = typename substitute<T, U>::type;

   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <template<class...> class Collector, class... Args, template <class...> class Original>
   struct substitute<Collector<Args...>, Original>
   {
      typedef Original<Args...> type;
   };
   
   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class ReturnType, class Collector>
   struct to_function;

   template <class ReturnType, template<class...> class Collector, class... Args>
   struct to_function<ReturnType, Collector<Args...>>
   {
      using type = ReturnType (&) (Args...);
   };
   
   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class ReturnType, class Collector>
   struct to_function_pointer;

   template <class ReturnType, template<class...> class Collector, class... Args>
   struct to_function_pointer<ReturnType, Collector<Args...>>
   {
      using type = ReturnType (*) (Args...);
   };
   
   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class ReturnType, class ClassType, class Collector>
   struct to_member_function_pointer;

   template <class ReturnType, class ClassType, template<class...> class Collector, class... Args>
   struct to_member_function_pointer<ReturnType, ClassType, Collector<Args...>>
   {
      using type = ReturnType (ClassType::*) (Args...);
   };

   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class...>
   struct variadic_helper;

   template <class... Args>
   using variadic_helper_t = typename variadic_helper<Args...>::type;
 
   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <template<class...> class Collector, class... Args, class C, class X, class Y>
   struct variadic_helper<Collector<Args...>, X, Y, C>
   {
      typedef typename replace_type<C, X, Y>::type current;
      typedef Collector<Args..., current> type;
   };
 
   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template
   <
      template <class...> class Collector
      , class... Args1
      , class C
      , class... Args2
      , class X
      , class Y
   >
   struct variadic_helper<Collector<Args1...>, X, Y, C, Args2...>
   {
      typedef typename replace_type<C, X, Y>::type current;
      typedef Collector<Args1..., current> collector_type;
      typedef typename variadic_helper<collector_type, X, Y, Args2...>::type type;
   };
}}

namespace tmeta
{
   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <template<class...> class T, class... Args, class X, class Y>
   struct replace_type<T<Args...>, X, Y>
   {
      typedef details::variadic_helper_t<details::collector<>, X, Y, Args...> parameters;
      typedef details::substitute_t<parameters, T> type;
      static bool const value = !tsl::is_same_v<T<Args...>, type>;
   };

   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class C, class X, class Y>
   struct replace_type<const volatile C, X, Y>
   {
      using type = typename details::cv_helper<C, X, Y>::type;
      static bool const value = !tsl::is_same_v<const volatile C, type>;
   };

   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
#define TMETA_REPLACE_TYPE(_qualifier)                                                             \
   template <class C, class X, class Y>                                                            \
   struct replace_type<C _qualifier, X, Y>                                                         \
   {                                                                                               \
      using type = tsl::conditional_t<tsl::is_same<C _qualifier, X>::value, Y,                     \
         replace_type_t<C, X, Y> _qualifier>;                                                      \
      static bool const value = !tsl::is_same_v<C, type>;                                          \
   };

   TMETA_REPLACE_TYPE(const);
   TMETA_REPLACE_TYPE(volatile);
   TMETA_REPLACE_TYPE(*);
   TMETA_REPLACE_TYPE(&);
   TMETA_REPLACE_TYPE(&&);
#undef TMETA_REPLACE_TYPE

   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class C, class X, class Y, unsigned N>
   struct replace_type<C[N], X, Y>
   {
      using type = tsl::conditional_t<tsl::is_same<C[N], X>::value, Y, replace_type_t<C, X, Y> [N]>;
      static bool const value = !tsl::is_same_v<C[N], type>;
   };

   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class T, class... Args, class X, class Y>
   struct replace_type<T(*)(Args...), X, Y>
   {
   private:
      using return_type = replace_type_t<T, X, Y>;
      using parameters = details::variadic_helper_t<details::collector<>, X, Y, Args...>;
   
   public:
      using type = typename details::to_function_pointer<return_type, parameters>::type;
      static bool const value = !tsl::is_same_v<T(*)(Args...), type>;
   };

   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class T, class... Args, class X, class Y>
   struct replace_type<T(&)(Args...), X, Y>
   {
   private:
      using return_type = replace_type_t<T, X, Y>;
      using parameters = details::variadic_helper_t<details::collector<>, X, Y, Args...>;

   public:
      using type = typename details::to_function<return_type, parameters>::type;
      static bool const value = !tsl::is_same_v<T(&)(Args...), type>;
   };

   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class T, class U, class... Args, class X, class Y>
   struct replace_type<T(U::*)(Args...), X, Y>
   {
   private:
      using return_type = replace_type_t<T, X, Y>;
      using class_type = replace_type_t<U, X, Y>;
      using parameters = details::variadic_helper_t<details::collector<>, X, Y, Args...>;

   public:
      using type =
         typename details::to_member_function_pointer<return_type, class_type, parameters>::type;
      static bool const value = !tsl::is_same_v<T(U::*)(Args...), type>;
   };

   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class C, class X, class Y>
   struct replace_type
   {
      typedef tsl::conditional_t<tsl::is_same_v<C, X>, Y, C> type;
      static bool const value = !tsl::is_same_v<C, type>;
   };
}
