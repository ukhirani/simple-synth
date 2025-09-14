/*
  ==============================================================================

    Filter.h
    Created: 14 Sep 2025 6:44:52pm
    Author:  ukhirani

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter  : public juce::Component,
                public Slider::Listener
{
public:
    Filter(SimpleSynthAudioProcessor&);
    ~Filter() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider *) override;

private:

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> FrequencyAttachment;


    Slider FrequencySlider;
    Label FrequencyLabel;

    SimpleSynthAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)


};
