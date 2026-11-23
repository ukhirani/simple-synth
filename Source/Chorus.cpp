#include "Chorus.h"

ChorusComponent::ChorusComponent (SimpleSynthAudioProcessor& p)
    : ui::KnobModule (p.tree, 5, "Chorus", {
        { "chorusMix", "Mix", ui::fmt::percent },
        { "chorusDepth", "Depth", ui::fmt::ms },
        { "chorusDetune", "Detune", ui::fmt::number (1) },
        { "chorusStereo", "Width", ui::fmt::number (2) }
    })
{
}
