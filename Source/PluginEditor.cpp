/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleSynthAudioProcessorEditor::SimpleSynthAudioProcessorEditor (SimpleSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), 
      processor (p), 
      oscComponent(p), 
      envComponent(p), 
      filterComponent(p),
      reverbComponent(p),
      crunchComponent(p),
      chorusComponent(p),
      visualiserComponent(1)
{
    // Set the editor's size
    setSize (950, 700);
    setResizable(true, true);
    
    // Add and make visible all components
    addAndMakeVisible(&envComponent);
    addAndMakeVisible(&oscComponent);
    addAndMakeVisible(&filterComponent);
    addAndMakeVisible(&visualiserComponent);
    addAndMakeVisible(&reverbComponent);
    addAndMakeVisible(&crunchComponent);
    addAndMakeVisible(&chorusComponent);

    
    // Configure visualizer
    visualiserComponent.setBufferSize(64);
    visualiserComponent.setSamplesPerBlock(4);
    visualiserComponent.setRepaintRate(60);

    //
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
    Rectangle<int> oscArea = area.removeFromTop(280).removeFromLeft(250);

    oscComponent.setBounds(oscArea.removeFromTop(40));
    envComponent.setBounds(oscArea);
    filterComponent.setBounds(oscArea.getRight(),40 ,60 ,240 );
    visualiserComponent.setBounds(filterComponent.getRight(),10 ,600 ,250);
    crunchComponent.setBounds(0,oscComponent.getBottom() + 230,300,700);
    reverbComponent.setBounds(crunchComponent.getRight(),oscComponent.getBottom() + 230,360,700);
    chorusComponent.setBounds(reverbComponent.getRight(),oscComponent.getBottom() + 230,370,700);




}



