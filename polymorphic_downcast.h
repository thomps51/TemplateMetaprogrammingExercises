#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 26 January 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tmeta::polymorphic_downcast (problem 2-2, 2-3)

#include <cassert>
#include <type_traits>
#include <tsl/type_traits/is_pointer.h>
#include <tsl/type_traits/is_reference.h>
#include <tsl/type_traits/remove_reference.h>

namespace tmeta
{
   template <class Target, class Source>
   inline Target
   polymorphic_downcast(Source * x);
      
   template <class Target, class Source>
   inline Target
   polymorphic_downcast(Source & x);
}

namespace tmeta
{
   // with type traits
   template <class Target, class Source>
   inline Target
   polymorphic_downcast(Source * x)
   {
      static_assert(tsl::is_pointer_v<Target>, "Target must be a reference type");
      assert(dynamic_cast<Target>(x) == x);
      return static_cast<Target>(x);
   }
      
   template <class Target, class Source>
   inline Target
   polymorphic_downcast(Source & x)
   {
      static_assert(tsl::is_reference_v<Target>, "Target must be a reference type");
      assert(dynamic_cast<tsl::remove_reference_t<Target> *>(&x) == &x);
      return static_cast<Target>(x);
   }

   // without type_traits
   /*
   template <class Target, class Source>
   inline Target
   polymorphic_downcast(Source * x)
   {
      assert(dynamic_cast<Target>(x) == x);
      return static_cast<Target>(x);
   }
      
   template <class Target, class Source>
   inline Target &
   polymorphic_downcast(Source & x)
   {
      assert(dynamic_cast<tsl::remove_reference_t<Target> *>(&x) == &x);
      return static_cast<Target>(x);
   }
   */

}
