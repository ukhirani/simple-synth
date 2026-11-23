#include "Oscillator.h"

Oscillator::Oscillator (SimpleSynthAudioProcessor& p)
    : ui::ModulePanel (1, "Oscillator"),
      wave     (p.tree, "wavetype", "Wave", { "Sine", "Sqr", "Saw" }),
      octave   (p.tree, "oscOct", "Oct"),
      semitone (p.tree, "oscSemi", "Semi"),
      level    (p.tree, "oscAmp", "Level", ui::fmt::percent),
      noise    (p.tree, "noiseAmp", "Noise", ui::fmt::percent)
{
    for (auto* c : std::initializer_list<juce::Component*> { &wave, &octave, &semitone, &level, &noise })
        addAndMakeVisible (c);
}

void Oscillator::resized()
{
    auto r = getContentBounds();

    // Right: two knobs, each one knob-cell wide.
    const int cell = r.getHeight() < 100 ? 64 : 72;
    noise.setBounds (r.removeFromRight (cell));
    level.setBounds (r.removeFromRight (cell));
    r.removeFromRight (ui::space::s3);

    // Left: wave selector over the two steppers.
    const int rowH = ui::size::knobLabelH + 2 + 24;
    wave.setBounds (r.removeFromTop (rowH));
    r.removeFromTop (r.getHeight() - rowH);
    auto steppers = r;
    const int half = (steppers.getWidth() - ui::space::s2) / 2;
    octave.setBounds (steppers.removeFromLeft (half));
    semitone.setBounds (steppers.removeFromRight (half));
}
