/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#include <elements/element/child_window.hpp>
#include <elements/element/traversal.hpp>
#include <elements/element/floating.hpp>
#include <elements/view.hpp>

namespace cycfi { namespace elements
{
   ////////////////////////////////////////////////////////////////////////////
   // movable_base
   ////////////////////////////////////////////////////////////////////////////
   void movable_base::keep_tracking(context const& ctx, tracker_info& track_info)
   {
      if (track_info.current != track_info.previous)
      {
         auto fl = find_parent<floating_element*>(ctx);
         if (fl)
         {
            auto p = track_info.movement();
            fl->bounds(fl->bounds().move(p.x, p.y));
            ctx.view.refresh();
         }
      }
   }
}}
