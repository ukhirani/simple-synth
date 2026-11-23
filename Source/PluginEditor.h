#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Envelope.h"
#include "Filter.h"
#include "Crunch.h"
#include "Chorus.h"
#include "ReverbComponent.h"
#include "Limiter.h"
#include "PresetPanel.h"
#include "UI/IndustrialLookAndFeel.h"
#include "UI/Controls.h"

class SimpleSynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit SimpleSynthAudioProcessorEditor (SimpleSynthAudioProcessor&);
    ~SimpleSynthAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void parentHierarchyChanged() override;

    static constexpr int defaultWidth  = 920;
    static constexpr int defaultHeight = 700;

private:
    juce::SharedResourcePointer<IndustrialLookAndFeel> lookAndFeel;

    SimpleSynthAudioProcessor& processor;

    Oscillator       oscComponent;
    Envelope         envComponent;
    Filter           filterComponent;
    CrunchComponent  crunchComponent;
    ChorusComponent  chorusComponent;
    ReverbComponent  reverbComponent;
    LimiterComponent limiterComponent;

    ui::ModulePanel scopePanel { 8, "Output" };
    ui::Scope       scope;

    PresetPanel presetPanel;
    juce::TooltipWindow tooltips { this, 600 };

    juce::Rectangle<int> topBar;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSynthAudioProcessorEditor)
};
