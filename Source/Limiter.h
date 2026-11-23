#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/Controls.h"

class LimiterComponent : public ui::KnobModule
{
public:
    explicit LimiterComponent (SimpleSynthAudioProcessor&);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LimiterComponent)
};
