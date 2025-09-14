/*
  ==============================================================================

    Oscillator.cpp
    Created: 7 Sep 2025 9:34:46am
    Author:  ukhirani

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscillator.h"

//==============================================================================



Oscillator::Oscillator(SimpleSynthAudioProcessor& p):processor(p)
{
    setSize (200, 200);
    FillComboBox();
    oscMenu.setJustificationType(Justification::centred);

    waveSelection = std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment>(
        new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wavetype", oscMenu)
    );

}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (juce::Graphics& g)
{
    addAndMakeVisible(&oscMenu);
    oscMenu.addListener(this);
}

void Oscillator::comboBoxChanged(juce::ComboBox* comboBox)
{
    if (comboBox == &oscMenu)
    {
        // Handle the combo box selection change
        int selectedId = oscMenu.getSelectedId();
        std::cout << selectedId <<" "<<oscMenu.getItemText(selectedId-1)<<std::endl;

        // Do something with the selectedId
    }
}

void Oscillator::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(10);
    oscMenu.setBounds(area.removeFromTop(20));
}

void Oscillator::FillComboBox()
{
    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Square", 2);
    oscMenu.addItem("Saw", 3);
    // oscMenu.setSelectedId(1);
}