#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class LimiterComponent  : public juce::Component
{
public:
    LimiterComponent(SimpleSynthAudioProcessor&);
    ~LimiterComponent() override;

    void initLimiterSlider(Slider &slider);
    void initLimiterLabel(const juce::String &labelText, Label &label);

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    //sliders
    Slider inputGainSlider;
    Slider outputLimitSlider;
    Slider attackMsSlider;
    Slider holdMsSlider;
    Slider releaseMsSlider;


    SimpleSynthAudioProcessor& processor;

    //labels
    Label inputGainLabel;
    Label outputLimitLabel;
    Label attackMsLabel;
    Label holdMsLabel;
    Label releaseMsLabel;

    // ParamRange inputGain{1};
    // ParamRange outputLimit{stfx::units::dbToGain(-3)};
    // ParamRange attackMs{20}, holdMs{0}, releaseMs{0};

    Label LimiterLabel;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> inputGainSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> outputLimitSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackMsSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> holdMsSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> releaseMsSliderAttachment;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LimiterComponent)
};
