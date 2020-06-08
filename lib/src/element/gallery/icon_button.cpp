/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#include <elements/element/gallery/icon_button.hpp>

namespace cycfi { namespace elements
{
   namespace
   {
      void draw_icon_button(
         context const& ctx
       , uint32_t code
       , float size
       , color color_
       , bool state
       , bool hilite
      )
      {
         float corner_radius = 6;
         auto const& theme = get_theme();

         color icon_color = theme.icon_color;
         if (state)
         {
            color_ = color_.level(0.9);
            icon_color = icon_color.level(2);
         }
         else
         {
            color_ = color_.opacity(0.5);
            icon_color = icon_color.level(0.7);
         }
         if (hilite)
         {
            icon_color = icon_color.opacity(icon_color.alpha + ((1.0 - icon_color.alpha) * 0.8));
         }

         // Draw Button Body
         draw_button(ctx.canvas, ctx.bounds, color_, corner_radius);

         // Draw Icon
         draw_icon(ctx.canvas, ctx.bounds.move(0.5, 0.5), code, size, icon_color);
      }
   }

   view_limits icon_button_image_base::limits(basic_context const& /*ctx*/) const
   {
      auto  size = _size * get_theme().icon_font_size * 1.8f;
      return { { size, size }, { size, size } };
   }

   element* icon_button_image_base::hit_test(context const& ctx, point p)
   {
      return ctx.bounds.includes(p) ? this : nullptr;
   }

   void icon_button_image::draw(context const& ctx)
   {
      bool  state = value() > 1;
      bool  hilite = value() & 1;
      draw_icon_button(
         ctx, _code, _size * get_theme().icon_font_size
       , _body_color, state, hilite
      );
   }

   void icon_button_image2::draw(context const& ctx)
   {
      bool  state = value() > 1;
      bool  hilite = value() & 1;
      draw_icon_button(
         ctx, state? _code1 : _code2
       , _size * get_theme().icon_font_size, _body_color, true, hilite
      );
   }
}}
