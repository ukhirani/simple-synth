/*
  ==============================================================================

    Filter.cpp
    Created: 14 Sep 2025 6:44:52pm
    Author:  ukhirani

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Filter.h"

//==============================================================================
Filter::Filter(SimpleSynthAudioProcessor& p):processor(p)
{

  FrequencySlider.setSliderStyle(Slider::LinearBarVertical);
  FrequencySlider.setRange(0.1f,22000.0f);
  FrequencySlider.setTextBoxStyle(Slider::TextBoxBelow,false,20.0,20.0);
  FrequencySlider.setValue(10000.0f);
  FrequencySlider.addListener(this);
  addAndMakeVisible(&FrequencySlider);

  FrequencyLabel.setText("Hz", NotificationType::dontSendNotification);
  FrequencyLabel.setJustificationType(Justification::centred);
  FrequencyLabel.setColour(Label::textColourId, Colours::black);
  addAndMakeVisible(&FrequencyLabel);

  FrequencyAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "frequency", FrequencySlider);



}

Filter::~Filter()
{
}

void Filter::paint (juce::Graphics& g)
{

  FrequencySlider.setColour (Slider::textBoxTextColourId, juce::Colours::black);
  FrequencyLabel.setColour (Slider::textBoxTextColourId, juce::Colours::black);


  //now majority of the part of the ui implementation of the filter is done already
  //the only thing that's left is to :
  //TODO: add filter values to the value tree state
  //TODO: add the filter object to the actual plugin editor






}

void Filter::resized()
{

  const int sliderWidth = 50;
  const int sliderHeight = 200;
  const int startX = 0;
  const int startY = 0;
  const int spacing = 20;

  FrequencySlider.setBounds(startX, startY, sliderWidth, sliderHeight);


  const int labelY = startY + sliderHeight + 5;
  const int labelWidth = 20;
  const int labelHeight = 20;

  FrequencyLabel.setBounds(FrequencySlider.getX() + (sliderWidth - labelWidth)/2, labelY, labelWidth, labelHeight);






}

void Filter::sliderValueChanged(Slider* slider) {
  if (slider == &FrequencySlider) {

  }
}
