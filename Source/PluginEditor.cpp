/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <ranges>

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
    setSize (910, 700);
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

    //h
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

    oscComponent.setBounds(0,0,270,280);
    envComponent.setBounds(oscComponent.getRight() - 10,0,250,280);
    filterComponent.setBounds(envComponent.getRight(),0 ,120 ,280 );
    crunchComponent.setBounds(0,oscComponent.getBottom(),300,700);
    reverbComponent.setBounds(crunchComponent.getRight(),oscComponent.getBottom() ,360,700);
    chorusComponent.setBounds(reverbComponent.getRight(),oscComponent.getBottom() ,370,700);

    visualiserComponent.setBounds(getLocalBounds().removeFromBottom(160).reduced(10));





}



