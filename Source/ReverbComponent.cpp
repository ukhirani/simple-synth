#include "ReverbComponent.h"

ReverbComponent::ReverbComponent (SimpleSynthAudioProcessor& p)
    : ui::KnobModule (p.tree, 6, "Reverb", {
        { "reverbDry", "Dry", ui::fmt::percent },
        { "reverbWet", "Wet", ui::fmt::percent },
        { "roomMs", "Room", ui::fmt::ms },
        { "lowCutoffFrequency", "Low", ui::fmt::hz },
        { "highCutoffFrequency", "High", ui::fmt::hz },
        { "rt20", "RT20", ui::fmt::ms }
    })
{
}
