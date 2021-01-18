/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#include <elements/element/child_window.hpp>
#include <elements/element/floating.hpp>
#include <elements/view.hpp>

namespace cycfi { namespace elements
{
   ////////////////////////////////////////////////////////////////////////////
   // movable_base
   ////////////////////////////////////////////////////////////////////////////
   bool movable_base::click(context const& ctx, mouse_button btn)
   {
      _tracking_subject = proxy_base::click(ctx, btn);
      if (!_tracking_subject)
         return tracker<proxy_base>::click(ctx, btn);
      return _tracking_subject;
   }

   void movable_base::drag(context const& ctx, mouse_button btn)
   {
      if (_tracking_subject)
         proxy_base::drag(ctx, btn);
      else
         tracker<proxy_base>::drag(ctx, btn);
   }

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

   ////////////////////////////////////////////////////////////////////////////
   // closable_element
   ////////////////////////////////////////////////////////////////////////////
   void close_floating_element(context& ctx, floating_element* fl)
   {
      ctx.view.remove(fl->shared_from_this());
   }
}}
