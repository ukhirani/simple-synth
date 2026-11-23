#include "Crunch.h"

CrunchComponent::CrunchComponent (SimpleSynthAudioProcessor& p)
    : ui::KnobModule (p.tree, 4, "Crunch", {
        { "fuzz", "Fuzz", ui::fmt::percent },
        { "drive", "Drive", ui::fmt::gainDb },
        { "tonehz", "Tone", ui::fmt::hz },
        { "cuthz", "Cut", ui::fmt::hz },
        { "outgain", "Out", ui::fmt::gainDb }
    })
{
}
