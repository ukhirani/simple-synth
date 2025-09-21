/*
  ==============================================================================

    Envelope.cpp
    Created: 14 Sep 2025 11:58:21am
    Author:  ukhirani

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Envelope.h"


//===============   ===============================================================
Envelope::Envelope(SimpleSynthAudioProcessor& p):processor(p)
{

    AttackSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    AttackSlider.setRange(0.1f,5000.0f);
    AttackSlider.setTextBoxStyle(Slider::TextBoxBelow,false,20.0,20.0);
    AttackSlider.setValue(100.0f);
    AttackSlider.addListener(this);
    addAndMakeVisible(&AttackSlider);

    EnvelopeLabel.setText("ENVELOPE",NotificationType::dontSendNotification);
    EnvelopeLabel.setJustificationType(Justification::centred);
    EnvelopeLabel.setColour(Label::textColourId, Colours::black);
    addAndMakeVisible(&EnvelopeLabel);

    // Initialize ADSR labels
    ALabel.setText("ATK", NotificationType::dontSendNotification);
    ALabel.setJustificationType(Justification::centred);
    ALabel.setColour(Label::textColourId, Colours::black);
    addAndMakeVisible(&ALabel);

    DLabel.setText("DEC", NotificationType::dontSendNotification);
    DLabel.setJustificationType(Justification::centred);
    DLabel.setColour(Label::textColourId, Colours::black);
    addAndMakeVisible(&DLabel);

    SLabel.setText("SUS", NotificationType::dontSendNotification);
    SLabel.setJustificationType(Justification::centred);
    SLabel.setColour(Label::textColourId, Colours::black);
    addAndMakeVisible(&SLabel);

    RLabel.setText("REL", NotificationType::dontSendNotification);
    RLabel.setJustificationType(Justification::centred);
    RLabel.setColour(Label::textColourId, Colours::black);
    addAndMakeVisible(&RLabel);

    DecaySlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    DecaySlider.setRange(0.1f,5000.0f);
    DecaySlider.setTextBoxStyle(Slider::TextBoxBelow,false,20.0,20.0);
    DecaySlider.setValue(100.0f);
    DecaySlider.addListener(this);
    addAndMakeVisible(&DecaySlider);

    SustainSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SustainSlider.setRange(0.1f,5000.0f);
    SustainSlider.setTextBoxStyle(Slider::TextBoxBelow,false,20.0,20.0);
    SustainSlider.setValue(100.0f);
    SustainSlider.addListener(this);
    addAndMakeVisible(&SustainSlider);

    ReleaseSlider.setSliderStyle(Slider::LinearBarVertical);
    ReleaseSlider.setRange(0.1f,500.0f);
    ReleaseSlider.setTextBoxStyle(Slider::TextBoxBelow,false,20.0,20.0);
    ReleaseSlider.setValue(100.0f);
    ReleaseSlider.addListener(this);
    addAndMakeVisible(&ReleaseSlider);




    attackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "attack", AttackSlider);
    decayAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "decay", DecaySlider);
    sustainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "sustain", SustainSlider);
    releaseAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "release", ReleaseSlider);



}

Envelope::~Envelope()
{
}

void Envelope::paint (juce::Graphics& g)
{
    int borderWidth = 2;
    auto border = juce::Rectangle<int>(
        AttackSlider.getX() ,
        10,
        (ReleaseSlider.getRight() - AttackSlider.getX() ),
        30
    );
    g.setColour(Colours::black);
    g.drawRect(border, borderWidth);

    g.drawRect(AttackSlider.getBounds(), borderWidth);
    g.drawRect(DecaySlider.getBounds(), borderWidth);
    g.drawRect(SustainSlider.getBounds(), borderWidth);
    g.drawRect(ReleaseSlider.getBounds(), borderWidth);




    AttackSlider.setColour (Slider::textBoxTextColourId, juce::Colours::black);
    // AttackSlider.setColour(Slider::ColourIds::)
    DecaySlider.setColour (Slider::textBoxTextColourId, juce::Colours::black);
    SustainSlider.setColour (Slider::textBoxTextColourId, juce::Colours::black);
    ReleaseSlider.setColour (Slider::textBoxTextColourId, juce::Colours::black);
}

void Envelope::resized()
{
    constexpr int sliderWidth = 50;
    constexpr int sliderHeight = 200;
    constexpr int startX = 10;
    constexpr int startY = 50;
    constexpr int spacing = 10;

    // Set bounds for sliders
    AttackSlider.setBounds(startX, startY, sliderWidth, sliderHeight);
    DecaySlider.setBounds(startX + sliderWidth + spacing, startY, sliderWidth, sliderHeight);
    SustainSlider.setBounds(startX + (sliderWidth + spacing) * 2, startY, sliderWidth, sliderHeight);
    ReleaseSlider.setBounds(startX + (sliderWidth + spacing) * 3, startY, sliderWidth, sliderHeight);

    // Set bounds for labels below sliders
    constexpr int labelY = startY + sliderHeight + 5;
    constexpr int labelWidth = 50;
    constexpr int labelHeight = 20;

    ALabel.setBounds(AttackSlider.getX() + (sliderWidth - labelWidth)/2, labelY, labelWidth, labelHeight);
    DLabel.setBounds(DecaySlider.getX() + (sliderWidth - labelWidth)/2, labelY, labelWidth, labelHeight);
    SLabel.setBounds(SustainSlider.getX() + (sliderWidth - labelWidth)/2, labelY, labelWidth, labelHeight);
    RLabel.setBounds(ReleaseSlider.getX() + (sliderWidth - labelWidth)/2, labelY, labelWidth, labelHeight);

    EnvelopeLabel.setBounds(10,15,ReleaseSlider.getRight()- AttackSlider.getX(),20);
}

void Envelope::sliderValueChanged(Slider* slider) {
    if (slider == &AttackSlider) {
        processor.AttackTime = AttackSlider.getValue();
    }else if (slider == &ReleaseSlider) {
        processor.ReleaseTime = ReleaseSlider.getValue();
    }else if (slider == &SustainSlider) {
        processor.SustainTime = SustainSlider.getValue();
    }else if (slider == &DecaySlider) {
        processor.DecayTime = DecaySlider.getValue();
    }
}
