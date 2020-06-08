/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(ELEMENTS_GALLERY_ICON_BUTTON_JUNE_5_2016)
#define ELEMENTS_GALLERY_ICON_BUTTON_JUNE_5_2016

#include <elements/element/element.hpp>
#include <elements/element/gallery/button.hpp>
#include <elements/support/theme.hpp>

namespace cycfi { namespace elements
{
   ////////////////////////////////////////////////////////////////////////////
   // Icon Button
   ////////////////////////////////////////////////////////////////////////////
   struct icon_button_image_base : element, basic_receiver<int>
   {
                              icon_button_image_base(
                                 float size
                               , color body_color = get_theme().default_button_color
                              )
                               : _size(size)
                               , _body_color(body_color)
                              {}

      view_limits             limits(basic_context const& ctx) const override;
      element*                hit_test(context const& ctx, point p) override;

      float                   _size;
      color                   _body_color;
   };

   struct icon_button_image : icon_button_image_base
   {
                              icon_button_image(
                                 uint32_t code
                               , float size
                               , color body_color = get_theme().default_button_color
                              )
                               : icon_button_image_base(size, body_color)
                               , _code(code)
                              {}

      void                    draw(context const& ctx) override;

      uint32_t                _code;
   };

   struct icon_button_image2 : icon_button_image_base
   {
                              icon_button_image2(
                                 uint32_t code1
                               , uint32_t code2
                               , float size
                               , color body_color = get_theme().default_button_color
                              )
                               : icon_button_image_base(size, body_color)
                               , _code1(code1)
                               , _code2(code2)
                              {}

      void                    draw(context const& ctx) override;

      uint32_t                _code1, _code2;
   };

   inline auto toggle_icon_button(
      uint32_t code
    , float size
    , color body_color = get_theme().default_button_color
   )
   {
      return toggle_button(icon_button_image{ code, size, body_color });
   }

   inline auto toggle_icon_button(
      uint32_t code1
    , uint32_t code2
    , float size
    , color body_color = get_theme().default_button_color
   )
   {
      return toggle_button(icon_button_image2{ code1, code2, size, body_color });
   }

   inline auto icon_button(
      uint32_t code
    , float size
    , color body_color = get_theme().default_button_color
   )
   {
      return toggle_button(icon_button_image{ code, size, body_color });
   }
}}

#endif
