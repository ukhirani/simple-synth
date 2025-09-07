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



Oscillator::Oscillator()
{
    setSize (200, 200);
    FillComboBox();
    oscMenu.setJustificationType(Justification::centred);
    
    // Make it visible
    addAndMakeVisible(&oscMenu);
    oscMenu.addListener(this);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (juce::Graphics& g)
{
    // Draw a background for the oscillator section
    g.fillAll(juce::Colours::darkgrey.darker(0.2f));
    g.setColour(juce::Colours::white);
    g.drawText("Oscillator", getLocalBounds().reduced(10), juce::Justification::top, true);
}

void Oscillator::comboBoxChanged(juce::ComboBox* comboBox)
{
    if (comboBox == &oscMenu)
    {
        // Handle the combo box selection change - handled by parameter attachment
        // No need for custom logic here
    }
}

void Oscillator::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(10);
    
    // Leave space for the title
    area.removeFromTop(20);
    
    // Place the combobox
    oscMenu.setBounds(area.removeFromTop(30).reduced(5, 0));
}

void Oscillator::FillComboBox()
{
    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Square", 2);
    oscMenu.addItem("Saw", 3);
    oscMenu.setSelectedId(1);
}