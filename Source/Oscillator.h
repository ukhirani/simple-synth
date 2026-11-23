#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/Controls.h"

// 01 OSC: waveform, pitch offsets and the two source levels.
class Oscillator : public ui::ModulePanel
{
public:
    explicit Oscillator (SimpleSynthAudioProcessor&);
    void resized() override;

private:
    ui::Segmented wave;
    ui::Stepper octave, semitone;
    ui::Knob level, noise;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
