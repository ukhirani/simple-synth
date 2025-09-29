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
    addAndMakeVisible(&oscMenu);
    oscMenu.addListener(this);

    addAndMakeVisible(oscLabel);
    oscLabel.setText("OSC", NotificationType::dontSendNotification);
    oscLabel.setFont(FontOptions(15.0f,Font::bold));
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

    OctaveSlider.setSliderStyle(Slider::SliderStyle::IncDecButtons);
    OctaveSlider.setRange(-3,+3,1);//TODO: use enums or pre-processor
    OctaveSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(&OctaveSlider);

    SemiToneSlider.setSliderStyle(Slider::SliderStyle::IncDecButtons);
    SemiToneSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    SemiToneSlider.setRange(-11,11,1);
    addAndMakeVisible(&SemiToneSlider);


    OscAmpSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    OscAmpSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(&OscAmpSlider);

    OscAmpLabel.setText("OSC-AMP", NotificationType::dontSendNotification);
    OscAmpLabel.setJustificationType(Justification::centred);
    OscAmpLabel.setColour(Label::textColourId, Colours::black);
    addAndMakeVisible(&OscAmpLabel);

    NoiseLabel.setText("NOISE", NotificationType::dontSendNotification);
    NoiseLabel.setJustificationType(Justification::centred);
    NoiseLabel.setColour(Label::textColourId, Colours::black);
    addAndMakeVisible(&NoiseLabel);

    OctaveLabel.setText("OCT", NotificationType::dontSendNotification);
    OctaveLabel.setJustificationType(Justification::centred);
    OctaveLabel.setColour(Label::textColourId, Colours::black);
    addAndMakeVisible(&OctaveLabel);

    SemiToneLabel.setText("SEM", NotificationType::dontSendNotification);
    SemiToneLabel.setJustificationType(Justification::centred);
    SemiToneLabel.setColour(Label::textColourId, Colours::black);
    addAndMakeVisible(&SemiToneLabel);



    waveSelection = std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment>(
    new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wavetype", oscMenu)
);
    noiseAmpSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "noiseAmp", noiseAmpSlider);
    oscAmpSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "oscAmp",OscAmpSlider);
    octaveSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "oscOct",OctaveSlider);
    semitoneAmpSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "oscSemi",SemiToneSlider);







}

Oscillator::~Oscillator()
{

}

void Oscillator::paint (juce::Graphics& g)
{
    constexpr int borderWidth = 2;
    g.setColour(Colours::black);

    g.drawRect(oscLabel.getBounds(), borderWidth);
    g.drawRect(oscMenu.getBounds(), borderWidth + 1);
    g.drawRect(noiseAmpSlider.getBounds(), borderWidth);
    g.drawRect(OscAmpSlider.getBounds(), borderWidth);



}

void Oscillator::comboBoxChanged(juce::ComboBox* comboBox)
{

}

void Oscillator::resized()
{
    int sliderWidth = 100;
    constexpr int sliderHeight = 170;
    constexpr int startX = 10;
    constexpr int startY = 10;
    constexpr int spacing = 10;

    constexpr int labelY = startY + sliderHeight + 5;
    constexpr int labelWidth = 50;
    constexpr int labelHeight = 20;

    oscMenu.setBounds(startX, 40 +  10, getLocalBounds().getWidth()-20, labelHeight);
    oscLabel.setBounds(startX,10,oscMenu.getWidth(),30);
    noiseAmpSlider.setBounds(startX, oscMenu.getBottom() + 10, sliderWidth, sliderHeight);

    OctaveLabel.setBounds(noiseAmpSlider.getRight()  + spacing,noiseAmpSlider.getY()-2,sliderWidth/2 + 5,labelHeight);
    SemiToneLabel.setBounds(noiseAmpSlider.getRight()  + spacing*2 + OctaveLabel.getWidth(),noiseAmpSlider.getY()-2,sliderWidth/2 + 5,labelHeight);

    OctaveSlider.setBounds(noiseAmpSlider.getRight()  + spacing,OctaveLabel.getBottom() + 1,sliderWidth/2 + 5 ,labelHeight);
    SemiToneSlider.setBounds(noiseAmpSlider.getRight()  + spacing*2 + OctaveLabel.getWidth(),OctaveLabel.getBottom() + 1,sliderWidth/2 + 5,labelHeight);

    sliderWidth+=18;
    OscAmpSlider.setBounds(noiseAmpSlider.getRight()+10,OctaveSlider.getBottom()+10,sliderWidth,(noiseAmpSlider.getHeight()-50));

    NoiseLabel.setBounds(10,noiseAmpSlider.getBottom() + 5, sliderWidth-18, labelHeight);
    OscAmpLabel.setBounds(spacing*2 + NoiseLabel.getWidth(),noiseAmpSlider.getBottom() + 5, sliderWidth, labelHeight);

}

void Oscillator::FillComboBox()
{
    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Square", 2);
    oscMenu.addItem("Saw", 3);
}