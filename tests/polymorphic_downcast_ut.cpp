#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 26 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

#include "../polymorphic_downcast.h"
#include "catch2/catch.hpp"

struct A
{
   virtual ~A() {}
};
struct B : A
{
};

using tmeta::polymorphic_downcast;

TEST_CASE("Test tmeta::polymorphic_downcast", "[polymorphic_downcast]")
{
   B b;
   A * a_ptr = &b;
   B * b_ptr = polymorphic_downcast<B *>(a_ptr);
   A & a_ref = b;
   B & b_ref = polymorphic_downcast<B &>(a_ref);
   //B b_ref = polymorphic_downcast<B>(a_ref);

}
