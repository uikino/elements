/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(ELEMENTS_GALLERY_TOGGLE_SELECTOR_JUNE_5_2016)
#define ELEMENTS_GALLERY_TOGGLE_SELECTOR_JUNE_5_2016

#include <elements/support/theme.hpp>
#include <elements/element/button.hpp>
#include <string>
#include <utility>

namespace cycfi { namespace elements
{
   ////////////////////////////////////////////////////////////////////////////
   // toggle_selector (e.g. check_box and radio_button where the small button
   // at the left followed by some text at the right of the button.)
   ////////////////////////////////////////////////////////////////////////////
   struct toggle_selector : element, basic_receiver<int>
   {
                              toggle_selector(std::string text)
                               : _text(std::move(text))
                              {}

      view_limits             limits(basic_context const& ctx) const override;

      std::string             _text;
   };

   inline view_limits toggle_selector::limits(basic_context const& ctx) const
   {
      auto& thm = get_theme();
      auto  size = measure_text(ctx.canvas, _text.c_str(), thm.label_font, thm.label_font_size);
      size.x += 15 + size.y + 10 + 15;
      return { { size.x, size.y }, { size.x, size.y } };
   }
}}

#endif
