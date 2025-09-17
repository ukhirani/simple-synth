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
      visualiserComponent(1)  // 1 channel visualizer
{
    // Set the editor's size
    setSize (1000, 700);
    setResizable(true, true);
    
    // Add and make visible all components
    addAndMakeVisible(&envComponent);
    addAndMakeVisible(&oscComponent);
    addAndMakeVisible(&filterComponent);
    
    // Configure visualizer
    addAndMakeVisible(&visualiserComponent);
    visualiserComponent.setBufferSize(64);
    visualiserComponent.setSamplesPerBlock(4);
    visualiserComponent.setRepaintRate(60);
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
    filterComponent.setBounds(oscArea.getRight(),40 ,60 ,240 );
    visualiserComponent.setBounds(filterComponent.getRight(),10 ,500 ,230);


}



