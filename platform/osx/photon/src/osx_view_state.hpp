/*=================================================================================================
   Copyright (c) 2016 Joel de Guzman

   Licensed under a Creative Commons Attribution-ShareAlike 4.0 International.
   http://creativecommons.org/licenses/by-sa/4.0/
=================================================================================================*/
#if !defined(PHOTON_GUI_LIB_OSX_VIEW_STATE_AUGUST_22_2016)
#define PHOTON_GUI_LIB_OSX_VIEW_STATE_AUGUST_22_2016

#include <Quartz/Quartz.h>
#include <photon/support/canvas.hpp>

namespace photon
{
   struct view_state
   {
      using view_state_ptr = std::shared_ptr<view_state>;

      view_state(view_state_ptr saved = view_state_ptr{})
       : font_attributes(nullptr)
       , text_align(canvas::baseline)
       , saved(saved)
      {}

      ~view_state()
      {
         if (font_attributes)
            CFRelease(font_attributes);
      }

      CFDictionaryRef   font_attributes;
      int               text_align;
      view_state_ptr    saved;
   };
}

#endif