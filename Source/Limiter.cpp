#include "Limiter.h"

LimiterComponent::LimiterComponent (SimpleSynthAudioProcessor& p)
    : ui::KnobModule (p.tree, 7, "Limiter", {
        { "inputGain", "Pre", ui::fmt::gainDb },
        { "outputLimit", "Ceil", ui::fmt::gainDb },
        { "attackMs", "Atk", ui::fmt::ms },
        { "holdMs", "Hold", ui::fmt::ms },
        { "releaseMs", "Rel", ui::fmt::ms }
    })
{
}
