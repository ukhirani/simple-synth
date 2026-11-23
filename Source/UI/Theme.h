#pragma once

#include <JuceHeader.h>
#include "BinaryData.h"

// Design tokens for the SimpleSynth editor.
//
// The values mirror the "industrial" Astryx theme used by the promo website
// (website/themes/industrial): dark-only, black & white only, square corners,
// IBM Plex Mono. Keep the two in sync when either changes.
namespace ui
{
    namespace colour
    {
        // --color-background-*  (black & white only)
        inline const juce::Colour body      { 0xff000000 };
        inline const juce::Colour surface   { 0xff0a0a0a };
        inline const juce::Colour raised    { 0xff161616 };
        inline const juce::Colour well      { 0xff000000 };

        // --color-border / --color-border-emphasized
        inline const juce::Colour hairline  { 0xff1f1f1f };
        inline const juce::Colour border    { 0xff2e2e2e };
        inline const juce::Colour borderHi  { 0xff515151 };

        // --color-text-*
        inline const juce::Colour text      { 0xffffffff };
        inline const juce::Colour textDim   { 0xff9d9d9d };
        inline const juce::Colour textMuted { 0xff5c5c5c };

        // --color-accent / --color-on-accent: white on black
        inline const juce::Colour accent    { 0xffffffff };
        inline const juce::Colour accentHi  { 0xffdddddd };
        inline const juce::Colour onAccent  { 0xff000000 };
    }

    // --spacing-* (4px base unit)
    namespace space
    {
        constexpr int s1 = 4;
        constexpr int s2 = 8;
        constexpr int s3 = 12;
        constexpr int s4 = 16;
        constexpr int s6 = 24;
    }

    namespace size
    {
        constexpr int border      = 1;
        constexpr int headerH     = 28;   // module header strip
        constexpr int topBarH     = 52;   // editor title bar
        constexpr int knob        = 52;   // knob diameter
        constexpr int knobLabelH  = 14;
        constexpr int knobValueH  = 16;
    }

    // IBM Plex Mono (OFL), embedded via juce_add_binary_data.
    inline juce::Typeface::Ptr monoRegular()
    {
        static auto tf = juce::Typeface::createSystemTypefaceFor (BinaryData::IBMPlexMonoRegular_ttf,
                                                                  BinaryData::IBMPlexMonoRegular_ttfSize);
        return tf;
    }

    inline juce::Typeface::Ptr monoSemiBold()
    {
        static auto tf = juce::Typeface::createSystemTypefaceFor (BinaryData::IBMPlexMonoSemiBold_ttf,
                                                                  BinaryData::IBMPlexMonoSemiBold_ttfSize);
        return tf;
    }

    inline juce::Font mono (float height, bool bold = false)
    {
        return juce::Font (juce::FontOptions (bold ? monoSemiBold() : monoRegular()).withHeight (height));
    }

    // Small uppercase label with a little tracking, the house style for captions.
    inline juce::Font caption (float height = 10.5f, bool bold = false)
    {
        return mono (height, bold).withExtraKerningFactor (0.08f);
    }
}
