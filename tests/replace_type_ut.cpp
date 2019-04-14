#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 21 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

#include <tsl/type_traits/is_same.h>
#include "../replace_type.h"
#include "catch2/catch.hpp"

using tmeta::replace_type_t;
using tsl::is_same_v;

#define TEST_TYPE(arg1, arg2, arg3, expected)                                                      \
   REQUIRE(is_same_v<replace_type_t<arg1, arg2, arg3>, expected> == true)

struct MyType1{};
struct MyType2{};
template <class...>
struct MyType3{};

template <class...>
struct GetType;

// To truly stress test this, I would need a random type generator and associated machinery to test
// the result.  Here's a crazy compile-time random number generator I could use:
// https://www.researchgate.net/publication/259005783_Random_number_generator_for_C_template_metaprograms
// The idea would be, have a list of base types, including templates, functions, etc.  Have a list
// of modifiers.  Randomly choose a base type, if its a template, randomly choose a number of args,
// then for each type chose a random number of modifiers, picking them at random.  Likely we would
// want a constant seed value, since we want to be able to reproduce failures if we are unable to
// generate meaningful output.

TEST_CASE("Test tmeta::replace_type", "[replace_type]")
{
   REQUIRE(is_same_v<replace_type_t<std::tuple<int, bool, long, long, int, bool>, int, char>,
              std::tuple<char, bool, long, long, char, bool>> == true);
   REQUIRE(is_same_v<replace_type_t<std::vector<int, std::allocator<int>>, int, long>,
              std::vector<long, std::allocator<long>>> == true);
   TEST_TYPE(std::vector<std::vector<std::vector<int>>>, int, char,
      std::vector<std::vector<std::vector<char>>>);
   TEST_TYPE(volatile const int, const int, long, volatile long);
   TEST_TYPE(volatile int, int, long, volatile long);
   TEST_TYPE(volatile const int, volatile int, long, const long);
   TEST_TYPE(void *, void, int, int *);
   TEST_TYPE(MyType3<int>, MyType3<int>, char, char);
   TEST_TYPE(MyType3<>, MyType3<>, char, char);
   TEST_TYPE(void *, long, int, void *);
   TEST_TYPE(void *, long, int, void *);
   TEST_TYPE(int * [5][4][3][2][1], int * [2][1], long *, long * [5][4][3]);  // See note!
   TEST_TYPE(int const * [10], int const, long, long * [10]);
   TEST_TYPE(int const * [10], int, long, long const * [10]);
   TEST_TYPE(int * const * [5][4][7][3][6][11], int * const *, long * const,
      long * const[5][4][7][3][6][11]);
   TEST_TYPE(char & (*)(char &), char &, long &, long & (*)(long &));
   TEST_TYPE(char & (*)(char &) noexcept, char &, long &, long & (*)(long &) noexcept);
   TEST_TYPE(char & (*)(), char &, long &, long & (*)());
   TEST_TYPE(char & (&)(char &), char &, long &, long & (&)(long &));
   TEST_TYPE(char & (MyType1::*)(char &), MyType1, MyType2, char & (MyType2::*)(char &));
   TEST_TYPE(char & (MyType1::*)(char &)const, MyType1, MyType2, char & (MyType2::*)(char &)const);
    TEST_TYPE(
      char & (MyType1::*)(char &)noexcept, MyType1, MyType2, char & (MyType2::*)(char &)noexcept);
   TEST_TYPE(char & (MyType1::*)(char &)const, MyType1, MyType2, char & (MyType2::*)(char &)const);
   TEST_TYPE(char & (MyType1::*)(char &)const noexcept, MyType1, MyType2,
      char & (MyType2::*)(char &)const noexcept);
   TEST_TYPE(char & (MyType1::*)(char &) const & noexcept, MyType1, MyType2,
      char & (MyType2::*)(char &)const & noexcept);

   // Yes, you can have pointers to variadic functions!
   using variadic_function_pointer_int = int (*) (char, ...) noexcept;
   using variadic_function_pointer_char = char (*) (char, ...) noexcept;
   REQUIRE(is_same_v<replace_type_t<variadic_function_pointer_int, int, char>,
              variadic_function_pointer_char> == true);
   using variadic_function_int = int (char, ...) noexcept;
   using variadic_function_char = char (char, ...) noexcept;
   REQUIRE(
      is_same_v<replace_type_t<variadic_function_int, int, char>, variadic_function_char> == true);
   using variadic_member_function_pointer_int = int (MyType1::*) (char, ...) noexcept;
   using variadic_member_function_pointer_char = char (MyType1::*) (char, ...) noexcept;
   REQUIRE(is_same_v<replace_type_t<variadic_member_function_pointer_int, int, char>,
              variadic_member_function_pointer_char> == true);
}
