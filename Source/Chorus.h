#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


class ChorusComponent  : public juce::Component
{
public:
    ChorusComponent(SimpleSynthAudioProcessor&);
    ~ChorusComponent() override;

    void initChorusSlider(Slider &slider);

    void initChorusLabel(const juce::String &labelText, Label &label);

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    SimpleSynthAudioProcessor& processor;

    Slider chorusMixSlider,chorusDepthSlider,chorusDetuneSlider,chorusStereoSlider;
    Label ChorusLabel,chorusMixLabel,chorusDepthLabel,chorusDetuneLabel,chorusStereoLabel;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> chorusMixSliderAttachment, chorusDepthSliderAttachment,chorusDetuneSliderAttachment,chorusStereoSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusComponent)
};
