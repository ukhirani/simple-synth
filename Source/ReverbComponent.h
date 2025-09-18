/*
  ==============================================================================

    ReverbComponent.h
    Created: 18 Sep 2025 1:08:30pm
    Author:  ukhirani

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class ReverbComponent  : public juce::Component
{
public:
    ReverbComponent(SimpleSynthAudioProcessor&);
    ~ReverbComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    Slider drySlider;
    Slider wetSlider;
    Slider RoomMsSlider;
    Slider LowCutoffFrequencySlider;
    Slider HighCutoffFrequencySlider;
    Slider RT20Slider;

    SimpleSynthAudioProcessor& processor;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> wetSliderAttachment;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};
