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
    setSize (500, 500);


    AttackSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    AttackSlider.setRange(0.1f,5000.0f);
    AttackSlider.setTextBoxStyle(Slider::TextBoxBelow,true,20.0,10.0);
    AttackSlider.setValue(100.0f);
    AttackSlider.addListener(this);
    addAndMakeVisible(&AttackSlider);

    sliderTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"attack",AttackSlider);

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

    AttackSlider.setBounds(10,10,40,100);
}

void SimpleSynthAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &AttackSlider)
    {
        processor.AttackTime = AttackSlider.getValue();

    }
}

