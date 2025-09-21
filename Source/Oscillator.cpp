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
    noiseAmpSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "noiseAmp", noiseAmpSlider);

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

    noiseAmpSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    noiseAmpSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(&noiseAmpSlider);

    NoiseLabel.setText("NOISE", NotificationType::dontSendNotification);
    NoiseLabel.setJustificationType(Justification::centred);
    NoiseLabel.setColour(Label::textColourId, Colours::black);
    addAndMakeVisible(NoiseLabel);

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
    g.drawRect(noiseAmpSlider.getBounds(), borderWidth);



}

void Oscillator::comboBoxChanged(juce::ComboBox* comboBox)
{

}

void Oscillator::resized()
{
    constexpr int sliderWidth = 100;
    constexpr int sliderHeight = 160;
    constexpr int startX = 10;
    constexpr int startY = 10;
    constexpr int spacing = 10;

    constexpr int labelY = startY + sliderHeight + 5;
    constexpr int labelWidth = 50;
    constexpr int labelHeight = 20;

    oscMenu.setBounds(10, 40 +  10, 250, labelHeight);
    oscLabel.setBounds(10,10,oscMenu.getWidth(),30);
    noiseAmpSlider.setBounds(10, oscMenu.getBottom() + 10, sliderWidth, sliderHeight);
    NoiseLabel.setBounds(10,noiseAmpSlider.getBottom() + 10, sliderWidth, labelHeight);
}

void Oscillator::FillComboBox()
{
    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Square", 2);
    oscMenu.addItem("Saw", 3);
    // oscMenu.setSelectedId(1);
}