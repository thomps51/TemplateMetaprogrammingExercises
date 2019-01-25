#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 20 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/
#include <tsl/type_traits/is_same.h>
#include "../add_const_ref.h"
#include "catch2/catch.hpp"

using tsl::is_same;
using tmeta::add_const_ref;

TEMPLATE_TEST_CASE( "Test tsl::add_const_ref", "[add_const_ref][template]", bool, char ) {
   REQUIRE(is_same<typename add_const_ref<TestType>::type, TestType const &>::value == true);
   REQUIRE(is_same<typename add_const_ref<TestType const>::type, TestType const &>::value == true);
   REQUIRE(
      is_same<typename add_const_ref<TestType const &>::type, TestType const &>::value == true);
   REQUIRE(is_same<typename add_const_ref<volatile TestType const &>::type,
              volatile TestType const &>::value
      == true);
   // This should fail to compile, see note in add_const_ref.h
   // REQUIRE(is_same<typename add_const_ref<TestType const &&>::type, TestType &>::value == true);
}
