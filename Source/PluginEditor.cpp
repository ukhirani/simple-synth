/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleSynthAudioProcessorEditor::SimpleSynthAudioProcessorEditor (SimpleSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 500);
    setResizable(true,true);


    AttackSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    AttackSlider.setRange(0.1f,5000.0f);
    AttackSlider.setTextBoxStyle(Slider::TextBoxBelow,false,20.0,20.0);
    AttackSlider.setValue(100.0f);
    AttackSlider.addListener(this);
    addAndMakeVisible(&AttackSlider);
    
    // Initialize ADSR labels
    ALabel.setText("A", NotificationType::dontSendNotification);
    ALabel.setJustificationType(Justification::centred);
    ALabel.setColour(Label::textColourId, Colours::black);
    addAndMakeVisible(&ALabel);
    
    DLabel.setText("D", NotificationType::dontSendNotification);
    DLabel.setJustificationType(Justification::centred);
    DLabel.setColour(Label::textColourId, Colours::black);
    addAndMakeVisible(&DLabel);
    
    SLabel.setText("S", NotificationType::dontSendNotification);
    SLabel.setJustificationType(Justification::centred);
    SLabel.setColour(Label::textColourId, Colours::black);
    addAndMakeVisible(&SLabel);
    
    RLabel.setText("R", NotificationType::dontSendNotification);
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



    /*
     * Using std::unique_ptr to properly manage SliderAttachment memory
     * This fixes the memory leak issue mentioned in the TODO
     */
    attackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "attack", AttackSlider);
    decayAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "decay", DecaySlider);
    sustainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "sustain", SustainSlider);
    releaseAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "release", ReleaseSlider);




}

SimpleSynthAudioProcessorEditor::~SimpleSynthAudioProcessorEditor()
{
}

//==============================================================================
void SimpleSynthAudioProcessorEditor::paint (juce::Graphics& g) {
    // Fill background
    g.fillAll (juce::Colours::white);
    
    // Set default text color to black for all text elements
    g.setColour (juce::Colours::black);
    
    // Set default font
    g.setFont (juce::FontOptions (15.0f));
    
    // Set text color for all sliders and labels
    AttackSlider.setColour (Slider::textBoxTextColourId, juce::Colours::black);
    DecaySlider.setColour (Slider::textBoxTextColourId, juce::Colours::black);
    SustainSlider.setColour (Slider::textBoxTextColourId, juce::Colours::black);
    ReleaseSlider.setColour (Slider::textBoxTextColourId, juce::Colours::black);
    
    // Set label colors
}

void SimpleSynthAudioProcessorEditor::resized()
{
    // Slider dimensions and positions
    const int sliderWidth = 50;
    const int sliderHeight = 200;
    const int startX = 10;
    const int startY = 10;
    const int spacing = 20;
    
    // Set bounds for sliders
    AttackSlider.setBounds(startX, startY, sliderWidth, sliderHeight);
    DecaySlider.setBounds(startX + sliderWidth + spacing, startY, sliderWidth, sliderHeight);
    SustainSlider.setBounds(startX + (sliderWidth + spacing) * 2, startY, sliderWidth, sliderHeight);
    ReleaseSlider.setBounds(startX + (sliderWidth + spacing) * 3, startY, sliderWidth, sliderHeight);
    
    // Set bounds for labels below sliders
    const int labelY = startY + sliderHeight + 5;
    const int labelWidth = 20;
    const int labelHeight = 20;
    
    ALabel.setBounds(AttackSlider.getX() + (sliderWidth - labelWidth)/2, labelY, labelWidth, labelHeight);
    DLabel.setBounds(DecaySlider.getX() + (sliderWidth - labelWidth)/2, labelY, labelWidth, labelHeight);
    SLabel.setBounds(SustainSlider.getX() + (sliderWidth - labelWidth)/2, labelY, labelWidth, labelHeight);
    RLabel.setBounds(ReleaseSlider.getX() + (sliderWidth - labelWidth)/2, labelY, labelWidth, labelHeight);
}

void SimpleSynthAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
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

