/*
  ==============================================================================

    Envelope.h
    Created: 14 Sep 2025 11:58:21am
    Author:  ukhirani

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Envelope  : public juce::Component,
                  public Slider::Listener
{
public:
    Envelope(SimpleSynthAudioProcessor&);
    ~Envelope() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;


private:

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

    Slider AttackSlider;
    Slider DecaySlider;
    Slider SustainSlider;
    Slider ReleaseSlider;

      // ADSR labels
    Label ALabel;
    Label DLabel;
    Label SLabel;
    Label RLabel;

    Label EnvelopeLabel;


    SimpleSynthAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
