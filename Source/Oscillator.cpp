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
    FillComboBox();
    oscMenu.setJustificationType(Justification::centred);

    waveSelection = std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment>(
        new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wavetype", oscMenu)
    );

    addAndMakeVisible(oscLabel);
    oscLabel.setText("OSC", NotificationType::dontSendNotification);
    oscLabel.setJustificationType(Justification::centred);
    oscLabel.setColour(Label::textColourId, Colours::black);
    cout<<oscLabel.getText();

    oscMenu.setColour(ComboBox::ColourIds::backgroundColourId, Colours::white);
    oscMenu.setColour(ComboBox::ColourIds::textColourId  , Colours::black);
    oscMenu.setColour(ComboBox::ColourIds::outlineColourId  , Colours::black);
    oscMenu.setColour(ComboBox::ColourIds::buttonColourId , Colours::black);
    oscMenu.setColour(ComboBox::ColourIds::arrowColourId , Colours::black);
    oscMenu.setColour(ComboBox::ColourIds::focusedOutlineColourId , Colours::black);









    addAndMakeVisible(&oscMenu);
    oscMenu.addListener(this);


}

Oscillator::~Oscillator()
{

}

void Oscillator::paint (juce::Graphics& g)
{
    constexpr int borderWidth = 2;
;
    g.setColour(Colours::black);

    g.drawRect(oscLabel.getBounds(), borderWidth);
    g.drawRect(oscMenu.getBounds(), borderWidth + 1);
    const auto area = getLocalBounds().removeFromBottom(210).reduced(10);
    g.drawRect(area, borderWidth );
    g.drawEllipse(area.getX()+5,area.getY()+5,area.getWidth()-10,area.getHeight()-10,borderWidth);


}

void Oscillator::comboBoxChanged(juce::ComboBox* comboBox)
{
    if (comboBox == &oscMenu)
    {
        // Handle the combo box selection change
        int selectedId = oscMenu.getSelectedId();
        // std::cout << selectedId <<" "<<oscMenu.getItemText(selectedId-1)<<std::endl;

        // Do something with the selectedId
    }
}

void Oscillator::resized()
{
    constexpr int sliderWidth = 50;
    constexpr int sliderHeight = 200;
    constexpr int startX = 10;
    constexpr int startY = 10;
    constexpr int spacing = 10;

    constexpr int labelY = startY + sliderHeight + 5;
    constexpr int labelWidth = 50;
    constexpr int labelHeight = 20;

    oscMenu.setBounds(10, 40 +  10, 250, labelHeight);
    oscLabel.setBounds(10,10,oscMenu.getWidth(),30);
}

void Oscillator::FillComboBox()
{
    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Square", 2);
    oscMenu.addItem("Saw", 3);
    // oscMenu.setSelectedId(1);
}