#include "PluginEditor.h"

SimpleSynthAudioProcessorEditor::SimpleSynthAudioProcessorEditor (SimpleSynthAudioProcessor& p)
    : AudioProcessorEditor (&p),
      processor (p),
      oscComponent (p),
      envComponent (p),
      filterComponent (p),
      crunchComponent (p),
      chorusComponent (p),
      reverbComponent (p),
      limiterComponent (p),
      scope (p.getScopeBuffer()),
      presetPanel (p, p.getPresetManger())
{
    setLookAndFeel (&lookAndFeel.get());

    // The standalone window (title bar, options button, dialogs) picks up the
    // default LookAndFeel; reset in the destructor before it can dangle.
    juce::LookAndFeel::setDefaultLookAndFeel (&lookAndFeel.get());

    for (auto* c : std::initializer_list<juce::Component*> {
             &oscComponent, &envComponent, &filterComponent,
             &crunchComponent, &chorusComponent,
             &reverbComponent, &limiterComponent,
             &scopePanel, &presetPanel })
        addAndMakeVisible (c);

    scopePanel.addAndMakeVisible (scope);

    setSize (defaultWidth, defaultHeight);
}

SimpleSynthAudioProcessorEditor::~SimpleSynthAudioProcessorEditor()
{
    if (&juce::LookAndFeel::getDefaultLookAndFeel() == &lookAndFeel.get())
        juce::LookAndFeel::setDefaultLookAndFeel (nullptr);

    setLookAndFeel (nullptr);
}

void SimpleSynthAudioProcessorEditor::parentHierarchyChanged()
{
    // Repaint the standalone window chrome with the new default LookAndFeel.
    if (auto* top = getTopLevelComponent(); top != nullptr && top != this)
        top->sendLookAndFeelChange();
}

void SimpleSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    using namespace ui;

    g.fillAll (colour::body);

    auto bar = topBar.reduced (space::s4, 0);

    // Wordmark: solid square + name + version.
    g.setColour (colour::text);
    g.fillRect (bar.getX(), bar.getCentreY() - 6, 12, 12);
    bar.removeFromLeft (12 + space::s3);

    g.setFont (mono (17.0f, true).withExtraKerningFactor (0.04f));
    const juce::String name ("SIMPLESYNTH");
    g.drawText (name, bar, juce::Justification::centredLeft, false);
    bar.removeFromLeft (juce::GlyphArrangement::getStringWidthInt (g.getCurrentFont(), name) + space::s3);

    g.setFont (caption (10.5f));
    g.setColour (colour::textMuted);
    g.drawText ("V" JucePlugin_VersionString "  /  POLY SYNTH", bar, juce::Justification::centredLeft, false);

    g.setColour (colour::border);
    g.fillRect (topBar.removeFromBottom (1));
}

void SimpleSynthAudioProcessorEditor::resized()
{
    using namespace ui;

    auto r = getLocalBounds();
    topBar = r.removeFromTop (size::topBarH);

    presetPanel.setBounds (topBar.reduced (space::s4, space::s3).removeFromRight (420));

    r.reduce (space::s3, space::s3);
    const int gap  = space::s2;
    const int rowH = 146;

    // Each row splits its width in proportion to how many knobs a module has.
    auto layoutRow = [gap] (juce::Rectangle<int> row, std::initializer_list<std::pair<juce::Component*, float>> items)
    {
        float total = 0.0f;
        for (auto& [c, w] : items) total += w;
        const int free = row.getWidth() - gap * ((int) items.size() - 1);
        int x = row.getX();
        size_t i = 0;
        for (auto& [c, w] : items)
        {
            const bool last = ++i == items.size();
            const int width = last ? row.getRight() - x : juce::roundToInt ((float) free * w / total);
            c->setBounds (x, row.getY(), width, row.getHeight());
            x += width + gap;
        }
    };

    layoutRow (r.removeFromTop (rowH), { { &oscComponent, 4.6f }, { &envComponent, 4.0f }, { &filterComponent, 2.0f } });
    r.removeFromTop (gap);
    layoutRow (r.removeFromTop (rowH), { { &crunchComponent, 5.0f }, { &chorusComponent, 4.0f } });
    r.removeFromTop (gap);
    layoutRow (r.removeFromTop (rowH), { { &reverbComponent, 6.0f }, { &limiterComponent, 5.0f } });
    r.removeFromTop (gap);

    scopePanel.setBounds (r);
    scope.setBounds (scopePanel.getContentBounds());
}
