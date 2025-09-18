/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Envelope.h"
#include "Filter.h"
#include "ReverbComponent.h"
#include <juce_audio_basics/juce_audio_basics.h>

//==============================================================================
/**
*/
class SimpleSynthAudioProcessorEditor  : public juce::AudioProcessorEditor

{
public:
    SimpleSynthAudioProcessorEditor (SimpleSynthAudioProcessor&);
    ~SimpleSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    // Method to push audio samples to the visualizer
    void pushNextSample(float sample) {
        visualiserComponent.pushSample(&sample, 1);
    }

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleSynthAudioProcessor& processor;
    Oscillator oscComponent;
    Envelope envComponent;
    Filter filterComponent;
    AudioVisualiserComponent visualiserComponent;
    ReverbComponent reverbComponent;

    




    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSynthAudioProcessorEditor)

};
