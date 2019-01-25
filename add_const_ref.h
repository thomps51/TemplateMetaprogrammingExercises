#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 19 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tmeta::add_const_ref (from exercise 2-0)

#include <tsl/preprocessor/disable_template.h>

namespace tmeta
{
    /* @brief
      Metafunction to add const and lvalue reference to type T.

      int -> int const &
      int const -> int const &
      int const & -> int const &

      @pre T is not a rvalue reference, see note below
     */
    template <class T>
    struct add_const_ref
    {
       typedef T const & type;
    };

    /* Notes: 
       Initially I just implemented the above and most types collapse how you expect, except for
       rvalue references.

       With the above, add_const_ref<MyType &&>::type will be MyType &.  This is unclear behavior, 
       and I don't think there is a well-defined result (at least one that anyone else looking at
       your code would expect), so I am disabling use with rvalue references below.
     */
    template <class T>
    struct add_const_ref<T &&>
    {
       TSL_DISABLE_TEMPLATE(T, "add_const_ref doesn't make sense for rvalue reference");
    };
}
