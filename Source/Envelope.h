#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/Controls.h"

class Envelope : public ui::KnobModule
{
public:
    explicit Envelope (SimpleSynthAudioProcessor&);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
