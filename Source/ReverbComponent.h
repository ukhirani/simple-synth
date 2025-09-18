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

    void initReverbSlider(Slider &);
    void initReverbLabel(juce::String label_text, Label &label);

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    //sliders
    Slider drySlider;
    Slider wetSlider;
    Slider RoomMsSlider;
    Slider LowCutoffFrequencySlider;
    Slider HighCutoffFrequencySlider;
    Slider RT20Slider;

    SimpleSynthAudioProcessor& processor;

    //labels
    Label dryLabel;
    Label wetLabel;
    Label roomMsLabel;
    Label lowCutLabel;
    Label highCutLabel;
    Label rt20Label;

    Label ReverbLabel;
    

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> wetSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> drySliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> roomMsSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lowCutoffFrequencySliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> highCutoffFrequencySliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> RT20SliderAttachment;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};
