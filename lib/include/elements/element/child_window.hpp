/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(ELEMENTS_CHILD_WINDOW_JANUARY_19_2021)
#define ELEMENTS_CHILD_WINDOW_JANUARY_19_2021

#include <elements/element/floating.hpp>
#include <elements/element/tracker.hpp>

namespace cycfi { namespace elements
{
   ////////////////////////////////////////////////////////////////////////////
   // Movable: allows an element (e.g. title_bar) to be movable if it is
   // contained inside a floating_element. The whole floating_element moves
   // when the element is dragged around.
   ////////////////////////////////////////////////////////////////////////////
   class movable_base : public tracker<proxy_base>
   {
   public:

      element*             hit_test(context const& ctx, point p) override;
      void                 keep_tracking(context const& ctx, tracker_info& track_info) override;
   };

   template <typename Subject>
   inline proxy<remove_cvref_t<Subject>, movable_base>
   movable(Subject&& subject)
   {
      return { std::forward<Subject>(subject) };
   }

   inline element* movable_base::hit_test(context const& ctx, point p)
   {
      return element::hit_test(ctx, p);
   }
}}

#endif
