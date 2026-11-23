#include "Envelope.h"

Envelope::Envelope (SimpleSynthAudioProcessor& p)
    : ui::KnobModule (p.tree, 2, "Amp Envelope", {
        { "attack", "Atk", ui::fmt::ms },
        { "decay", "Dec", ui::fmt::ms },
        { "sustain", "Sus", ui::fmt::number (1) },
        { "release", "Rel", ui::fmt::ms }
    })
{
}
