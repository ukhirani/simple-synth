/*
  ==============================================================================

    Oscillator.h
    Created: 7 Sep 2025 9:34:46am
    Author:  ukhirani

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator  : public juce::Component,
                    public juce::ComboBox::Listener
{
public:
    Oscillator(SimpleSynthAudioProcessor&);
    ~Oscillator() override;

    void comboBoxChanged(juce::ComboBox* comboBox) override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void FillComboBox();



private:
    ComboBox oscMenu;
    Label oscLabel;

    Slider noiseAmpSlider;
    Label NoiseLabel;

    Label OctaveLabel,SemiToneLabel,OscAmpLabel;    //TODO: make both sliders and labels visible
    Slider OctaveSlider,SemiToneSlider,OscAmpSlider; //TODO: make processor-value-tree-state and attach sliders to it

    SimpleSynthAudioProcessor& processor;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> noiseAmpSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
