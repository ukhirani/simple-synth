#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/Controls.h"

class CrunchComponent : public ui::KnobModule
{
public:
    explicit CrunchComponent (SimpleSynthAudioProcessor&);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CrunchComponent)
};
