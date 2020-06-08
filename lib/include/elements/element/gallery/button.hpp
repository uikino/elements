/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(ELEMENTS_GALLERY_BUTTON_JUNE_5_2016)
#define ELEMENTS_GALLERY_BUTTON_JUNE_5_2016

#include <elements/element/button.hpp>
#include <elements/element/misc.hpp>
#include <elements/element/label.hpp>
#include <elements/element/align.hpp>
#include <elements/element/margin.hpp>
#include <elements/element/tile.hpp>
#include <elements/support/theme.hpp>
#include <infra/support.hpp>
#include <string_view>
#include <utility>

namespace cycfi { namespace elements
{
   ////////////////////////////////////////////////////////////////////////////
   // Buttons
   ////////////////////////////////////////////////////////////////////////////
   template <typename Subject>
   struct basic_button_body : proxy<Subject>, basic_receiver<int>
   {
      using base_type = proxy<Subject>;
      using base_type::base_type;
      constexpr static float corner_radius = 4.0;

                              basic_button_body(color body_color, Subject subject);

      void                    draw(context const& ctx) override;
      element*                hit_test(context const& ctx, point p) override;
      void                    prepare_subject(context& ctx) override;

      color                   body_color;
   };

   template <typename Subject>
   inline basic_button_body<Subject>::basic_button_body(color body_color, Subject subject)
    : base_type(std::move(subject))
    , body_color(body_color)
   {}

   void draw_button_base(
      context const& ctx
    , bool state
    , bool hilite
    , rect bounds
    , color color_
    , float corner_radius
   );

   template <typename Subject>
   inline void basic_button_body<Subject>::draw(context const& ctx)
   {
      bool  state = this->value() > 1;
      bool  hilite = this->value() & 1;
      draw_button_base(ctx, state, hilite, ctx.bounds, body_color, corner_radius);
      base_type::draw(ctx);
   }

   template <typename Subject>
   inline element* basic_button_body<Subject>::hit_test(context const& ctx, point p)
   {
      return ctx.bounds.includes(p) ? this : nullptr;
   }

   template <typename Subject>
   inline void basic_button_body<Subject>::prepare_subject(context& ctx)
   {
      bool  state = this->value() > 1;
      if (state)
         ctx.bounds = ctx.bounds.move(1, 1);
   }

   ////////////////////////////////////////////////////////////////////////////
   // Basic buttons
   ////////////////////////////////////////////////////////////////////////////
   template <typename Base, typename Subject, typename... Arg>
   inline proxy<remove_cvref_t<Subject>, Base>
   make_button(Subject&& subject, Arg&& ...arg)
   {
      return { std::forward<Subject>(subject), std::forward<Arg>(arg)... };
   }

   template <typename Base, typename Subject, typename... Arg>
   inline basic_toggle_button<proxy<remove_cvref_t<Subject>, Base>>
   make_toggle_button(Subject&& subject, Arg&& ...arg)
   {
      return { std::forward<Subject>(subject), std::forward<Arg>(arg)... };
   }

   template <typename Base, typename Subject, typename... Arg>
   inline basic_latching_button<proxy<remove_cvref_t<Subject>, Base>>
   make_latching_button(Subject&& subject, Arg&& ...arg)
   {
      return { std::forward<Subject>(subject), std::forward<Arg>(arg)... };
   }

   template <typename Subject>
   inline typename std::enable_if<
      std::is_base_of_v<element, remove_cvref_t<Subject>>
    , proxy<remove_cvref_t<Subject>, basic_button>
   >::type
   button(Subject&& subject)
   {
      return make_button<basic_button>(std::forward<Subject>(subject));
   }

   template <typename Subject>
   inline typename std::enable_if<
      std::is_base_of_v<element, remove_cvref_t<Subject>>
    , basic_toggle_button<proxy<remove_cvref_t<Subject>, basic_button>>
   >::type
   toggle_button(Subject&& subject)
   {
      return make_toggle_button<basic_button>(std::forward<Subject>(subject));
   }

   template <typename Subject>
   inline typename std::enable_if<
      std::is_base_of_v<element, remove_cvref_t<Subject>>
    , basic_latching_button<proxy<remove_cvref_t<Subject>, basic_button>>
   >::type
   latching_button(Subject&& subject)
   {
      return make_latching_button<basic_button>(std::forward<Subject>(subject));
   }

   ////////////////////////////////////////////////////////////////////////////
   // Generic button factory
   ////////////////////////////////////////////////////////////////////////////
   template <typename Label>
   inline auto make_button_image(
      Label&& label
    , color body_color = get_theme().default_button_color
   )
   {
      return basic_button_body<Label>(body_color, label);
   }

   inline auto make_button_image(
      std::string text
    , float size = 1.0
    , color body_color = get_theme().default_button_color
   )
   {
      return make_button_image(
         margin(
            get_theme().button_margin,
            align_center(label(std::move(text)).relative_font_size(size))
         ),
         body_color
      );
   }

   inline auto make_button_image(
      std::uint32_t icon_code
    , float size = 1.0
    , color body_color = get_theme().default_button_color
   )
   {
      return make_button_image(
         margin(
            get_theme().button_margin,
            align_center(
               icon(icon_code, size)
            )
         ),
         body_color
      );
   }

   inline auto make_button_image(
      std::uint32_t icon_code
    , std::string text
    , float size = 1.0
    , color body_color = get_theme().default_button_color
   )
   {
      return make_button_image(
         margin(
            get_theme().button_margin,
            align_center(
               htile(
                  right_margin(8, icon(icon_code, size)),
                  label(std::move(text)).relative_font_size(size)
               )
            )
         ),
         body_color
      );
   }

   inline auto make_button_image(
      std::string text
    , std::uint32_t icon_code
    , float size = 1.0
    , color body_color = get_theme().default_button_color
   )
   {
      return make_button_image(
         margin(
            get_theme().button_margin,
            align_center(
               htile(
                  label(std::move(text)).relative_font_size(size),
                  left_margin(12, icon(icon_code, size))
               )
            )
         ),
         body_color
      );
   }

   ////////////////////////////////////////////////////////////////////////////
   // Standard button factories
   ////////////////////////////////////////////////////////////////////////////
   inline auto button(
      std::string text
    , float size = 1.0
    , color body_color = get_theme().default_button_color
   )
   {
      return button(make_button_image(std::move(text), size, body_color));
   }

   inline auto button(
      std::uint32_t icon_code
    , float size = 1.0
    , color body_color = get_theme().default_button_color
   )
   {
      return button(make_button_image(icon_code, size, body_color));
   }

   inline auto button(
      std::uint32_t icon_code
    , std::string text
    , float size = 1.0
    , color body_color = get_theme().default_button_color
   )
   {
      return button(make_button_image(icon_code, std::move(text), size, body_color));
   }

   inline auto button(
      std::string text
    , std::uint32_t icon_code
    , float size
    , color body_color = get_theme().default_button_color
   )
   {
      return button(make_button_image(std::move(text), icon_code, size, body_color));
   }

   inline auto toggle_button(
      std::string text
    , float size = 1.0
    , color body_color = get_theme().default_button_color
   )
   {
      return toggle_button(make_button_image(std::move(text), size, body_color));
   }

   inline auto toggle_button(
      std::uint32_t icon_code
    , float size = 1.0
    , color body_color = get_theme().default_button_color
   )
   {
      return toggle_button(make_button_image(icon_code, size, body_color));
   }

   inline auto toggle_button(
      std::uint32_t icon_code
    , std::string text
    , float size = 1.0
    , color body_color = get_theme().default_button_color
   )
   {
      return toggle_button(make_button_image(icon_code, std::move(text), size, body_color));
   }

   inline auto toggle_button(
      std::string text
    , std::uint32_t icon_code
    , float size
    , color body_color = get_theme().default_button_color
   )
   {
      return toggle_button(make_button_image(std::move(text), icon_code, size, body_color));
   }

   inline auto latching_button(
      std::string text
    , float size = 1.0
    , color body_color = get_theme().default_button_color
   )
   {
      return latching_button(make_button_image(std::move(text), size, body_color));
   }

   inline auto latching_button(
      std::uint32_t icon_code
    , float size = 1.0
    , color body_color = get_theme().default_button_color
   )
   {
      return latching_button(make_button_image(icon_code, size, body_color));
   }

   inline auto latching_button(
      std::uint32_t icon_code
    , std::string text
    , float size = 1.0
    , color body_color = get_theme().default_button_color
   )
   {
      return latching_button(make_button_image(icon_code, std::move(text), size, body_color));
   }

   inline auto latching_button(
      std::string text
    , std::uint32_t icon_code
    , float size
    , color body_color = get_theme().default_button_color
   )
   {
      return latching_button(make_button_image(std::move(text), icon_code, size, body_color));
   }

   ////////////////////////////////////////////////////////////////////////////
   // Text Buttons
   ////////////////////////////////////////////////////////////////////////////
   template <bool no_frame, typename Label>
   inline auto make_text_button_image(Label&& label)
   {
      if constexpr(no_frame)
         return label;
      else
         return layer(std::forward<Label>(label), frame{});
   }

   template <bool no_frame>
   inline auto make_text_button_image(
      std::string text
    , float size = 1.0
   )
   {
      return make_text_button_image<no_frame>(
         margin(
            get_theme().button_margin,
            align_left(label(std::move(text)).relative_font_size(size))
         )
      );
   }

   template <bool no_frame>
   inline auto make_text_button_image(
      std::uint32_t icon_code
    , float size = 1.0
   )
   {
      return make_text_button_image<no_frame>(
         margin(
            get_theme().button_margin,
            align_center(icon(icon_code, size))
         )
      );
   }

   template <bool no_frame>
   inline auto make_text_button_image(
      std::uint32_t icon_code
    , std::string text
    , float size = 1.0
   )
   {
      return make_text_button_image<no_frame>(
         margin(
            get_theme().button_margin,
            htile(
               align_left(right_margin(8, icon(icon_code, size))),
               align_right(label(std::move(text)).relative_font_size(size))
            )
         )
      );
   }

   template <bool no_frame>
   inline auto make_text_button_image(
      std::string text
    , std::uint32_t icon_code
    , float size = 1.0
   )
   {
      return make_text_button_image<no_frame>(
         margin(
            get_theme().button_margin,
            htile(
               align_left(label(std::move(text)).relative_font_size(size)),
               align_right(left_margin(12, icon(icon_code, size)))
            )
         )
      );
   }

   template <typename Base, bool no_frame = false, typename Label, typename... Arg>
   inline auto text_button(Label&& label)
   {
      return button<Base>(make_text_button_image<no_frame>(std::forward<Label>(label)));
   }

   template <typename Base, bool no_frame = false>
   inline auto text_button(
      std::string text
    , float size = 1.0
   )
   {
      return button<Base>(make_text_button_image<no_frame>(std::move(text), size));
   }

   template <typename Base, bool no_frame = false>
   inline auto text_button(
      std::uint32_t icon_code
    , float size = 1.0
   )
   {
      return button<Base>(make_text_button_image<no_frame>(icon_code, size));
   }

   template <typename Base, bool no_frame = false>
   inline auto text_button(
      std::uint32_t icon_code
    , std::string text
    , float size = 1.0
   )
   {
      return button<Base>(make_text_button_image<no_frame>(icon_code, std::move(text), size));
   }

   template <typename Base, bool no_frame = false>
   inline auto text_button_image(
      std::string text
    , std::uint32_t icon_code
    , float size = 1.0
   )
   {
      return button<Base>(make_text_button_image<no_frame>(move(text), icon_code, size));
   }
}}

#endif
