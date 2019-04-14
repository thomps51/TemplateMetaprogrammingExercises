#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 18 February 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

#include <tsl/type_traits/is_same.h>
#include "../type_descriptor.h"
#include "catch2/catch.hpp"
#include <sstream>

using tmeta::type_descriptor;
using std::ostream;

#define TEST_TYPE_DESCRIPTOR(_type)                                                                \
   ss << type_descriptor<_type>();                                                                 \
   REQUIRE(ss.str() == #_type);                                                                    \
   ss.str(std::string());                                                                          \
   ss.clear();

TEST_CASE("Test tmeta::type_descriptor", "[type_descriptor]")
{
   std::stringstream ss;
   TEST_TYPE_DESCRIPTOR(int);
   TEST_TYPE_DESCRIPTOR(char *);
   TEST_TYPE_DESCRIPTOR(short int const);
   TEST_TYPE_DESCRIPTOR(long int const);
   TEST_TYPE_DESCRIPTOR(long int const * &);
}
