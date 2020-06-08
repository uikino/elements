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
   // plain_button_image: Use this as a generic button body. The subject
   // determines how the button will look like.
   ////////////////////////////////////////////////////////////////////////////
   template <typename Subject>
   struct plain_button_image : proxy<Subject>, basic_receiver<int>
   {
      using base_type = proxy<Subject>;
      using base_type::base_type;

                              plain_button_image(Subject subject);

      void                    draw(context const& ctx) override;
      element*                hit_test(context const& ctx, point p) override;
   };

   template <typename Subject>
   inline plain_button_image<Subject>::plain_button_image(Subject subject)
    : base_type(std::move(subject))
   {}

   template <typename Subject>
   inline void plain_button_image<Subject>::draw(context const& ctx)
   {
      base_type::draw(ctx);
   }

   template <typename Subject>
   inline element* plain_button_image<Subject>::hit_test(context const& ctx, point p)
   {
      return ctx.bounds.includes(p) ? this : nullptr;
   }

   template <typename Subject>
   inline auto make_plain_button_image(Subject&& subject)
   {
      return plain_button_image<Subject>(std::forward<Subject>(subject));
   }

   ////////////////////////////////////////////////////////////////////////////
   // basic_button_image: Use this as a generic button body. The subject
   // will be drawn on top of a filled round-rect.
   ////////////////////////////////////////////////////////////////////////////
   template <typename Subject>
   struct basic_button_image : proxy<Subject>, basic_receiver<int>
   {
      using base_type = proxy<Subject>;
      using base_type::base_type;
      constexpr static float corner_radius = 4.0;

                              basic_button_image(color body_color, Subject subject);

      void                    draw(context const& ctx) override;
      element*                hit_test(context const& ctx, point p) override;
      void                    prepare_subject(context& ctx) override;

      color                   body_color;
   };

   template <typename Subject>
   inline basic_button_image<Subject>::basic_button_image(color body_color, Subject subject)
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
   inline void basic_button_image<Subject>::draw(context const& ctx)
   {
      bool  state = this->value() > 1;
      bool  hilite = this->value() & 1;
      draw_button_base(ctx, state, hilite, ctx.bounds, body_color, corner_radius);
      base_type::draw(ctx);
   }

   template <typename Subject>
   inline element* basic_button_image<Subject>::hit_test(context const& ctx, point p)
   {
      return ctx.bounds.includes(p) ? this : nullptr;
   }

   template <typename Subject>
   inline void basic_button_image<Subject>::prepare_subject(context& ctx)
   {
      bool  state = this->value() > 1;
      if (state)
         ctx.bounds = ctx.bounds.move(1, 1);
   }

   ////////////////////////////////////////////////////////////////////////////
   // Lowest level generic button factories (user supplied Base). This is the
   // basis of all button factories.
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

   ////////////////////////////////////////////////////////////////////////////
   // Basic button factories (based on basic_button)
   ////////////////////////////////////////////////////////////////////////////
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
   // Button image factories
   ////////////////////////////////////////////////////////////////////////////
   template <typename Label>
   inline auto make_button_image(
      Label&& label
    , color body_color = get_theme().default_button_color
   )
   {
      return basic_button_image<Label>(body_color, label);
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
   // Text button image factories. These image factories make plain button
   // images based on plain_button_image.
   ////////////////////////////////////////////////////////////////////////////
   template <bool no_frame, typename Label>
   inline auto make_text_button_image(Label&& label)
   {
      if constexpr(no_frame)
         return make_plain_button_image(label);
      else
         return make_plain_button_image(layer(std::forward<Label>(label), frame{}));
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

   ////////////////////////////////////////////////////////////////////////////
   // Text button factories. These image factories make plain buttons based
   // on plain_button_image.
   ////////////////////////////////////////////////////////////////////////////
   template <typename Base, bool no_frame = false, typename Label, typename... Arg>
   inline auto make_text_button(Label&& label, Arg&& ...arg)
   {
      return make_button<Base>(
         make_text_button_image<no_frame>(std::forward<Label>(label))
       , std::forward<Arg>(arg)...
      );
   }

   template <bool no_frame = false, typename Label>
   inline auto text_button(Label&& label)
   {
      return button(make_text_button_image<no_frame>(std::forward<Label>(label)));
   }

   template <bool no_frame = false>
   inline auto text_button(
      std::string text
    , float size = 1.0
   )
   {
      return button(make_text_button_image<no_frame>(std::move(text), size));
   }

   template <bool no_frame = false>
   inline auto text_button(
      std::uint32_t icon_code
    , float size = 1.0
   )
   {
      return button(make_text_button_image<no_frame>(icon_code, size));
   }

   template <bool no_frame = false>
   inline auto text_button(
      std::uint32_t icon_code
    , std::string text
    , float size = 1.0
   )
   {
      return button(make_text_button_image<no_frame>(icon_code, std::move(text), size));
   }

   template <bool no_frame = false>
   inline auto text_button_image(
      std::string text
    , std::uint32_t icon_code
    , float size = 1.0
   )
   {
      return button(make_text_button_image<no_frame>(move(text), icon_code, size));
   }
}}

#endif
