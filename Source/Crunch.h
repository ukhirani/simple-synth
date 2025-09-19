#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class CrunchComponent  : public juce::Component
{
public:
    CrunchComponent(SimpleSynthAudioProcessor&);
    ~CrunchComponent() override;

    void initCrunchSlider(Slider &slider);
    void initCrunchLabel(const juce::String &labelText, Label &label);

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    //sliders
    Slider fuzzSlider;
    Slider driveSlider;
    Slider tonehzSlider;
    Slider cuthzSlider;
    Slider outgainSlider;
    

    SimpleSynthAudioProcessor& processor;

    //labels
    Label fuzzLabel;
    Label driveLabel;
    Label tonehzLabel;
    Label cuthzLabel;
    Label outgainLabel;

    Label CrunchLabel;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> fuzzSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> driveSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> tonehzSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> cuthzSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> outgainSliderAttachment;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CrunchComponent)
};
