/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#include <elements/element/gallery/button.hpp>
#include <utility>

namespace cycfi { namespace elements
{
   void draw_button_base(
      context const& ctx
    , bool state
    , bool hilite
    , rect bounds
    , color color_
    , float corner_radius
   )
   {
      if (state)
      {
         bounds = bounds.move(1, 1);
         color_ = color_.opacity(0.5);
      }
      else
      {
         color_ = color_.level(0.9);
      }
      if (hilite)
      {
         color_ = color_.opacity(color_.alpha + ((1.0 - color_.alpha) * 0.4));
      }
      draw_button(ctx.canvas, bounds, color_, corner_radius);
   }
}}
