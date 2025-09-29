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

    Label OctaveLabel,SemiToneLabel,OscAmpLabel;
    Slider OctaveSlider,SemiToneSlider,OscAmpSlider;

    SimpleSynthAudioProcessor& processor;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> noiseAmpSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> octaveSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> semitoneAmpSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> oscAmpSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
