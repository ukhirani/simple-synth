#pragma once

#include <JuceHeader.h>
#include "BinaryData.h"

// Design tokens for the SimpleSynth editor.
//
// The values mirror the "industrial" Astryx theme used by the promo website
// (website/themes/industrial): dark-only, square corners, IBM Plex Mono, one
// signal-orange accent. Keep the two in sync when either changes.
namespace ui
{
    namespace colour
    {
        // --color-background-*
        inline const juce::Colour body      { 0xff1a1c1f };
        inline const juce::Colour surface   { 0xff23262a };
        inline const juce::Colour raised    { 0xff2b2f34 };
        inline const juce::Colour well      { 0xff141618 };

        // --color-border / --color-border-emphasized
        inline const juce::Colour hairline  { 0x1affffff };
        inline const juce::Colour border    { 0xff3a3e43 };
        inline const juce::Colour borderHi  { 0xff4e5358 };

        // --color-text-*
        inline const juce::Colour text      { 0xffffffff };
        inline const juce::Colour textDim   { 0xff999ea4 };
        inline const juce::Colour textMuted { 0xff6b7076 };

        // --color-accent (+ the lighter fill Astryx uses on dark tracks)
        inline const juce::Colour accent    { 0xffff5a1f };
        inline const juce::Colour accentHi  { 0xffff794a };
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
