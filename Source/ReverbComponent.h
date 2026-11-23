#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/Controls.h"

class ReverbComponent : public ui::KnobModule
{
public:
    explicit ReverbComponent (SimpleSynthAudioProcessor&);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};
