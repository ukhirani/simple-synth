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


    AttackSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    AttackSlider.setRange(0.1f,5000.0f);
    AttackSlider.setTextBoxStyle(Slider::TextBoxBelow,true,200.0,20.0);
    AttackSlider.setValue(100.0f);
    AttackSlider.addListener(this);
    addAndMakeVisible(&AttackSlider);

    DecaySlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    DecaySlider.setRange(0.1f,5000.0f);
    DecaySlider.setTextBoxStyle(Slider::TextBoxBelow,true,200.0,20.0);
    DecaySlider.setValue(100.0f);
    DecaySlider.addListener(this);
    addAndMakeVisible(&DecaySlider);

    SustainSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SustainSlider.setRange(0.1f,5000.0f);
    SustainSlider.setTextBoxStyle(Slider::TextBoxBelow,true,200.0,20.0);
    SustainSlider.setValue(100.0f);
    SustainSlider.addListener(this);
    addAndMakeVisible(&SustainSlider);

    ReleaseSlider.setSliderStyle(Slider::LinearBarVertical);
    ReleaseSlider.setRange(0.1f,500.0f);
    ReleaseSlider.setTextBoxStyle(Slider::TextBoxBelow,true,200.0,20.0);
    ReleaseSlider.setValue(100.0f);
    ReleaseSlider.addListener(this);
    addAndMakeVisible(&ReleaseSlider);



    new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "attack", AttackSlider);
    new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", DecaySlider);
    new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "sustain", SustainSlider);
    new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "release", ReleaseSlider);


}

SimpleSynthAudioProcessorEditor::~SimpleSynthAudioProcessorEditor()
{
}

//==============================================================================
void SimpleSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);

    g.setColour (juce::Colours::black);
    g.setFont (juce::FontOptions (15.0f));

}

void SimpleSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor.

    AttackSlider.setBounds(10,10,200,200);
    DecaySlider.setBounds(210,10,200,200);
    SustainSlider.setBounds(410,10,200,200);
    ReleaseSlider.setBounds(610,10,200,200);
}

void SimpleSynthAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &AttackSlider) {
        processor.AttackTime = AttackSlider.getValue();
    }else if (slider == &ReleaseSlider) {
        processor.ReleaseTime = ReleaseSlider.getValue();
    }
}

