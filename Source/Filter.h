#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter  : public juce::Component
{
public:
    Filter(SimpleSynthAudioProcessor&);
    ~Filter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> FrequencyAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> ResonanceAttachment;


    Slider FrequencySlider;
    Label FrequencyLabel;

    Slider ResonanceSlider;
    Label ResonanceLabel;

    Label FilterLabel;

    SimpleSynthAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Filter)
};
