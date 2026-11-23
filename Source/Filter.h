#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/Controls.h"

class Filter : public ui::KnobModule
{
public:
    explicit Filter (SimpleSynthAudioProcessor&);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
