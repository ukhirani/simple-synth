/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleSynthAudioProcessorEditor::SimpleSynthAudioProcessorEditor (SimpleSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), oscComponent(p), envComponent(p), filterComponent(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 700);

    setResizable(true,true);
    addAndMakeVisible(&envComponent);
    addAndMakeVisible(&oscComponent);
    addAndMakeVisible(&filterComponent);

    


}

SimpleSynthAudioProcessorEditor::~SimpleSynthAudioProcessorEditor()
{
}

//==============================================================================
void SimpleSynthAudioProcessorEditor::paint (juce::Graphics& g) {

    g.fillAll (juce::Colours::white);
    g.setColour (juce::Colours::black);
    g.setFont (juce::FontOptions (15.0f));

}

void SimpleSynthAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds();
    Rectangle<int> oscArea = area.removeFromTop(300).removeFromLeft(250);
    

    constexpr int componentWidth = 400;
    constexpr int componentHeight = 400;


    oscComponent.setBounds(oscArea.removeFromTop(40));
    envComponent.setBounds(oscArea);
    filterComponent.setBounds(oscArea.getRight(),40 ,100 ,240 );


}



