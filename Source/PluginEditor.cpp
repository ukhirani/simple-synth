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
      limiterComponent(p),
      visualiserComponent(1)
{
    // Set the editor's size
    setSize (910, 770);
    // setResizable(true, true);
    
    // Add and make visible all components
    addAndMakeVisible(&envComponent);
    addAndMakeVisible(&oscComponent);
    addAndMakeVisible(&filterComponent);
    addAndMakeVisible(&visualiserComponent);
    addAndMakeVisible(&reverbComponent);
    addAndMakeVisible(&crunchComponent);
    addAndMakeVisible(&chorusComponent);
    addAndMakeVisible(&limiterComponent);

    
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
    g.setFont (juce::FontOptions (25.0f,Font::bold));

    g.drawRect(area,3);

    int HeadingHeight = 20;


    g.drawFittedText("SYNTH8", area.getX() + 15,area.getCentreY() - HeadingHeight/2 , 100, HeadingHeight,juce::Justification::centredLeft, 1);

}

void SimpleSynthAudioProcessorEditor::resized()
{
    area = getLocalBounds().removeFromTop(80).reduced(10);

    const int startY = area.getBottom();

    oscComponent.setBounds(0,startY,250,280);
    envComponent.setBounds(oscComponent.getRight() - 10,startY,250,280);
    filterComponent.setBounds(envComponent.getRight(),startY ,120 ,280);
    crunchComponent.setBounds(filterComponent.getRight() - 10,startY + 10,300,300);
    chorusComponent.setBounds(0,oscComponent.getBottom() ,240,700);
    reverbComponent.setBounds(chorusComponent.getRight(),oscComponent.getBottom() ,360,700);
    limiterComponent.setBounds(crunchComponent.getX(),oscComponent.getBottom() ,300,300);
    visualiserComponent.setBounds(getLocalBounds().removeFromBottom(160).reduced(10));





}



