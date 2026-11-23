#include "Filter.h"

Filter::Filter (SimpleSynthAudioProcessor& p)
    : ui::KnobModule (p.tree, 3, "Filter", {
        { "frequency", "Cutoff", ui::fmt::hz },
        { "resonance", "Res", ui::fmt::number (2) }
    })
{
}
