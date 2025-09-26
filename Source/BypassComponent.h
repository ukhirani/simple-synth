#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class BypassComponent  : public juce::Component
{
public:
    BypassComponent(SimpleSynthAudioProcessor&);
    ~BypassComponent() override;

    void changeButtonUI(TextButton* button) {
        addAndMakeVisible(button);
        button->setColour(TextButton::ColourIds::buttonColourId, Colours::white);
        button->setColour(TextButton::ColourIds::textColourOffId, Colours::black);
    }

    void paint (juce::Graphics&) override;
    void resized() override;



private:
    SimpleSynthAudioProcessor& processor;
    TextButton toggleReverb,toggleCrunch,toggleChorus,toggleLimiter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BypassComponent)
};
