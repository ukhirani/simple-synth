/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "Chorus.h"
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Envelope.h"
#include "Filter.h"
#include "ReverbComponent.h"
#include "Crunch.h"
#include "Limiter.h"

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
    CrunchComponent crunchComponent;
    ChorusComponent chorusComponent;
    LimiterComponent limiterComponent;

    Rectangle<int> area;

    




    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSynthAudioProcessorEditor)

};
